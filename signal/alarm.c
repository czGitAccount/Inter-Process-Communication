#include "stdio.h"
#include "sys/types.h"
#include "signal.h"
#include "stdlib.h"
#include "unistd.h"
int main() {
    printf("alarm before\n");   
    alarm(9);
    printf("alarm before\n");
    int i = 0;
    while (i < 20) {
        i++;
        sleep(1);
        printf("process things, i = %d \n", i);
    }
    return 0;
}