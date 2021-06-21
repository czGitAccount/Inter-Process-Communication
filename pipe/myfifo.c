#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
int main() {
    int ret;
    ret = mkfifo("./myfifo", 777); // 权限 777
    if (ret < 0) {
        printf("create myfifo failure \n");
        return -1;
    }
    printf("create myfifo success \n");
    return 0;
}