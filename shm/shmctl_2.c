#include "sys/types.h"
#include "sys/shm.h"
#include "signal.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

// 信号处理函数，不需要任何处理，主要为了唤醒 pause 函数，且避免 sigusr1/2终止函数
void myfun(int signum) {return;}

int main(int argc, char* argv[]) {
    int shmid;
    int key;
    char* p;
    int pid;
    shmid = shmget(IPC_PRIVATE, 128, IPC_CREAT | 0777);
    if (shmid < 0) {
        printf("creat share memory failure\n");
        return -1;
    }
    printf("creat memory success shmid = %d\n", shmid);
    
    // shmget 在 fork 之前
    pid = fork();
    if (pid > 0) {
        signal(SIGUSR2, myfun);
        p = (char *)shmat(shmid, NULL, 0);
        if (p == NULL) {
            printf("shmat function failure\n");
            return -3;
        }
        while(1) {
            // write share memory
            printf("parent process start write share memory: \n");
            fgets(p, 128, stdin);
            kill(pid, SIGUSR1); // 通知子进程去读
            pause(); // 等待子进程去读
        }
    }
    if (pid == 0) {
        signal(SIGUSR1, myfun);
        p = (char *) shmat(shmid, NULL, 0);
        while(1) {
            pause(); // 等待父进程去写
            printf("share memory data: %s\n", p);
            kill(getppid(), SIGUSR2);
        }
    }
    return 0;
}