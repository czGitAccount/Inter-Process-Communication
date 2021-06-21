#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "sys/types.h"
#include "fcntl.h"
int main() {
    int fd;
    char process_inter = 0;
    fd = open("./myfifo", O_WRONLY);
    if (fd < 0) {
        printf("open myfifo failure\n");
        return -1;
    }
    printf("open myfifo success \n");
    int i;
    for (i = 0; i < 5; i++) {
        printf("this is first process i = %d\n", i);
        usleep(100);
    }
    process_inter = 1;
    sleep(3);
    write(fd, &process_inter, 1);
    while(1);
    return 0;
}