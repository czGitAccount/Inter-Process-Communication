#include "stdio.h"
#include "sys/types.h"
#include "signal.h"
#include "stdlib.h"
int main() {
    // printf("raise before");
    printf("raise before\n"); 
    raise(9);
    printf("raise after\n");
    return 0;
}
