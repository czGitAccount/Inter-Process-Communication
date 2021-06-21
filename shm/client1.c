#include "sys/types.h"
#include "sys/shm.h"
#include "signal.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

struct mybuf{
    int pid;
    char buf[124];
};

// 信号处理函数，不需要任何处理，主要为了唤醒 pause 函数，且避免 sigusr1/2终止函数
void myfun(int signum) {return;}

int main() {
    int shmid;
    int key;
    struct mybuf* p;
    int pid;
    // 创建 key
    key = ftok("./a.c",'c');
    if (key < 0) {
        printf("create key failure\n");
        return -1;
    }
    printf("create key success, key = %X\n", key);
    // 创建 share memory
    shmid = shmget(key, 128, IPC_CREAT | 0777);
    if (shmid < 0) {
        printf("creat share memory failure\n");
        return -2;
    }
    printf("creat memory success shmid = %d\n", shmid);  
    // 信号处理
    signal(SIGUSR1, myfun);
    // 地址映射
    p = (struct mybuf*)shmat(shmid, NULL, 0);
    if (p == NULL) {
        printf("shmat function failure\n");
        return -3;
    }
      
    // get server pid
    // read share memory
    pid = p->pid;
    // write client pid to share memory
    p->pid = getpid();
    kill(pid, SIGUSR2);
    
    // client start read data from share memory
    
    while(1) {
        pause(); // wait server write data to share memory;
        printf("client process receive data from share memory: %s", p->buf);
        kill(pid, SIGUSR2); // server may write share memory
    }    
    return 0;
}