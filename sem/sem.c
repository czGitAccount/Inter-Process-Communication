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

// child thread code
void *fun(char* var) {
    int j;
    // p wait
    // sem_wait(&sem);
    mysembuf.sem_op = -1;
    semop(semid, &mysembuf, 1);
    for (j = 0; j < 10; j++) {  // second
        usleep(100);
        printf("this is fun j = %d\n", j);
    }
}
// main thread code
int main () {
    char str[] = "hello linux\n";
    pthread_t tid;
    int ret;
    // 创建信号灯
    semid = semget(IPC_PRIVATE, 3, 0777);
    if (semid < 0) {
        printf("create semaphore failure\n");
        return -1;
    }
    printf("create semaphore success\n");
    system("ipcs -s");
    
    // sem_init(&sem, 0, 0); // sem = 0;
    // 信号量的初始化
    mysemun.val = 0;
    semctl(semid, 0, SETVAL, mysemun);
    mysembuf.sem_num = 0;
    mysembuf.sem_flg = 0; // 阻塞操作
    
    ret = pthread_create(&tid, NULL, fun, (void *)str);
    if (ret < 0) {
        printf("create thread failure\n");
        return -1;
    }
    int i;
    for (i = 0; i < 10; i++) { // first
        usleep(100);
        printf("this is main fun, i = %d\n", i);
    }
    // v
    // sem_post(&sem);
    mysembuf.sem_op = 1;
    semop(semid, &mysembuf, 1);
    
    while(1);
    return 0;
}