#include "stdio.h"
#include "sys/types.h"
#include "signal.h"
#include "stdlib.h"
#include "unistd.h"
int main() {
    printf("pause before \n");
    pause();
    printf("pause after \n");
    int i = 0;
    while (i < 20) {
        i++;
        sleep(1);
        printf("process things, i = %d", i);
    }
    return 0;
}