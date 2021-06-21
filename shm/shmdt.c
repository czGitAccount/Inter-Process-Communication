#include "sys/types.h"
#include "sys/shm.h"
#include "signal.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
int main() {
    int shmid;
    int key;
    char *p;
    key = ftok("./a.c", 'a');
    if (key < 0) {
        printf("create key failure\n");
        return -2;
    }
    printf("create key success, key = %X\n", key);
    shmid = shmget(key, 128, IPC_CREAT | 0777); 
    // shmid = shmget(IPC_PRIVATE, 128, 0777); 对比
    if (shmid < -1) {
        printf("create share memory failure\n");
        return -1;
    }
    printf("creat share memory success shmid = %d\n", shmid);
    system("ipcs -m");
    
    p = (char *)shmat(shmid, NULL, 0);
    if (p == NULL) {
        printf("shmat function failure\n");
        return -3;
    }
    // write share memory
    // stdin:键盘输入，128字节，写入 p 中
    fgets(p, 128, stdin);
    
    // start read share memory
    printf("share memory data: %s\n", p);
    printf("share memory data: %s\n", p);
    
    // 释放用户空间共享内存
    shmdt(p);
    memcpy(p, "abcd", 4);
    
    return 0;
}