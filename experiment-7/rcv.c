#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#define N 128
#define SIZE sizeof(struct msgbuf) - sizeof(long)
struct msgbuf{
 long mtype;
 int a;
 char b;
 char buf[N];
};
int main(int argc, const char *argv[])
{
	int msqid;
	struct msgbuf msg;
	if((msqid = msgget (12345,IPC_CREAT|IPC_EXCL|0644)) < 0){
		if(errno != EEXIST){
			perror("msgget error");
			return -1;
		}
		else{
			msqid = msgget(12345,0644);
		}
	}
	msgrcv(msqid,&msg,SIZE,100,0);
	printf("a=%d b=%c buf=%s\n",msg.a,msg.b,msg.buf);//这里有缓冲区，要加‘/n’
	printf("hello\n");
	system("ipcs -q");
	return 0;
}
