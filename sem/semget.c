#include "sys/types.h"
#include "sys/sem.h"
#include "signal.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"

int main() {
    int semid;
    semid = semget(IPC_PRIVATE, 3, 0777);
    if (semid < 0) {
        printf("create semaphore failure\n");
        return -1;
    }
    printf("create semaphore success, semid = %d\n", semid);
    system("ipcs -s");
    
    return 0;
}