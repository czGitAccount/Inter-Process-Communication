#include "unistd.h"
#include "stdio.h"
#include "sys/types.h"
#include "stdlib.h"

int main() {
    pid_t pid;
    int process_inter = 0;
    pid = fork();
    if (pid == 0) { // child process code second
        int i = 0;
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
    }
    return 0;
}
