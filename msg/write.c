#include "sys/types.h"
#include "sys/msg.h"
#include "signal.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

struct msgbuf {
    long type;
    char voltage[124];
    char ID[4];
};

int main() {
    int msgid;
    struct msgbuf sendbuf;
    struct msgbuf recvbuf;
    int readret;
    int key;
    key = ftok("./a.c", 'c');
    if (key < 0) {
        printf("creat key failure\n");
        return -1;
    }
    msgid = msgget(key,IPC_CREAT | 0777);
    if (msgid < 0) {
        printf("create message queue failure\n");
        return -1;
    }
    printf("create message queue success, msgid = %d\n", msgid);
    system("ipcs -q");
    
    sendbuf.type = 100;
    // write message queue
    while (1) {
        // init sendbuf
        memset(sendbuf.voltage, 0, 124);
        
        printf("please input message:\n");
        fgets(sendbuf.voltage, 124, stdin);
        
        // start write message to message queue
    	msgsnd(msgid, (void *)&sendbuf, strlen(sendbuf.voltage), 0);
    }
    
    // delete message queue 
    msgctl(msgid, IPC_RMID, NULL);
    system("ipcs -q");
    
    return 0;
}