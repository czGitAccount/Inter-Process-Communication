#include "stdio.h"
#include "sys/types.h"
#include "signal.h"
#include "stdlib.h"
#include "unistd.h"
#include "sys/wait.h"
int main() {
    pid_t pid;
    pid = fork();
    if (pid > 0) {
        sleep(8);
        if (waitpid(pid, NULL, WNOHANG) == 0) {
            kill(pid, 9); // 杀死子进程，此时父进程没有对其进行回收资源(wait)
                          // 子进程会变成僵尸进程
        }
        wait(NULL);
        while(1);
    }
    if (pid == 0) {
        printf("raise function before\n");
        raise(SIGTSTP); // 进程进入暂停状态（T）
        printf("raise function after\n");
        exit(0);
    }
    return 0;
}