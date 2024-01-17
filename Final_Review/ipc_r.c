#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <string.h>
#define N 128
#define SIZE sizeof(struct msgbuf) - sizeof(long)
struct msgbuf {
        long mtype;
        int a;
        char b;
        char buf[N];
};
int main()
{
	int msqid;
	struct msgbuf msg;
	key_t key;
	key = ftok(".",'a');
	msqid = msgget(key, 0664);
	msgrcv(msqid,&msg,SIZE,0,0);
	printf("a=%d,b=%c,buf=%s\n",msg.a,msg.b,msg.buf);
	system("ipcs -q");
	return 0;
}
