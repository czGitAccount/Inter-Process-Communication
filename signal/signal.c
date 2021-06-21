#include "stdio.h"
#include "sys/types.h"
#include "signal.h"
#include "stdlib.h"
#include "unistd.h"
void myfun(int signum) {
    int i = 0;
    while (i < 10) {
        printf("process signal signum = %d, i = %d\n", signum);
        sleep(1);
        i++;
    }
    return; // return main
}
int main() {
    signal(14, myfun);
    printf("alarm before \n");
    alarm(9);
    printf("alarm after \n");
    // signal(14, SIG_IGN);  // 又一次接收到信号，忽略它，不会处理myfun，也不会终止运行
    signal(14, SIG_DFL);  // 默认处理，9秒后终止
    int i = 0;
    while (i < 15) {
        i++;
        sleep(1);
        printf("process things, i = %d\n", i);
    }
    return 0;
}