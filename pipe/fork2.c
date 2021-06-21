#include "unistd.h"
#include "stdio.h"
#include "sys/types.h"
#include "stdlib.h"

int main() {
    pid_t pid;
    char process_inter = 0;
    int fd[2];
    int ret;
    // 创建管道
    ret = pipe(fd);
    if (ret < 0) {
        printf("create pipe failure\n");
        return -1;
    } else printf("create pipe success\n");
    
    pid = fork();
    if (pid == 0) { // child process code second
        int i = 0;
        // if pipe empty  sleep
        read(fd[0], &process_inter, 1); //需要注意该process与父进程process同名而已
        while (process_inter == 0);
        for (int i = 0; i < 5; i++) {
            printf("this is child process i = %d\n", i);
            usleep(100);
        }
    }
    if (pid > 0) { // parent process code first
    	int i = 0;
        for (int i = 0; i < 5; i++) {
            printf("this iparent process i = %d\n", i);
            usleep(100);
        }
        process_inter = 1;
	sleep(5);
        write(fd[1], &process_inter, 1);
    }
    return 0;
}
