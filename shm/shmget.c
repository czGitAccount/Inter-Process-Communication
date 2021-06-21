#include "sys/types.h"
#include "sys/shm.h"
#include "signal.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
int main() {
    int shmid;
    int key;
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
    // system("ipcrm -m shmid");
    return 0;
}