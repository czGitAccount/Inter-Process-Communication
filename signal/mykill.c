#include "sys/types.h"
#include "signal.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"

int main(int argc, char *argv[]) {
    int sig;
    int pid;
    if (argc < 3) {
        printf("please input param\n");
        return -1;
    }
    sig = atoi(argv[1]);
    pid = atoi(argv[2]);
    printf("sig = %d, pid = %d \n", sig, pid);
    // 调用系统函数
    kill(pid, sig);
    return 0;
}