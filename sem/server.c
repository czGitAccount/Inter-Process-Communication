#include "stdio.h"
#include "stdlib.h"
#include "pthread.h"
#include "sys/ipc.h"
#include "sys/sem.h"

// 定义信号量
// sem_t sem;
// 定于信号灯联合体
union semun {
    int              val;    /* Value for SETVAL */
    struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
    unsigned short  *array;  /* Array for GETALL, SETALL */
    struct seminfo  *__buf;  /* Buffer for IPC_INFO (Linux-specific) */
};

int semid;
union semun mysemun;
struct sembuf mysembuf;

// main thread code
int main () {
    // 创建 key
	int key;
    key = ftok("./a.c", 'a');
    if (key < 0) {
        printf("create key failure\n");
        return -1;
    }
    printf("create key success\n");
    
    // 创建信号灯
    semid = semget(key, 3, IPC_CREAT | 0777);
    if (semid < 0) {
        printf("create semaphore failure\n");
        return -2;
    }
    printf("create semaphore success, semid = %d\n", semid);
    system("ipcs -s");
    
	// 初始化信号  让client先运行，让client完成初始化即可，client 会使用 P 操作
    // mysemun.val = 0;
    // semctl(semid, 0, SETVAL, mysemun);
    mysembuf.sem_num = 0;
    mysembuf.sem_flg = 0; // 阻塞操作

    int i;
    for (i = 0; i < 10; i++) { // first
        usleep(100);
        printf("server fun, i = %d\n", i);
    }
    sleep(3);
    // v
    mysembuf.sem_op = 1;
    semop(semid, &mysembuf, 1);
    
    while(1);
    return 0;
}