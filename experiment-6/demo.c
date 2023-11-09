#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
int main()
{
	int msqid,pid;
	struct msgbuf
	{
		long mtype;
		char buf[1024];
	}msg;
	msqid=msgget(123,IPC_CREAT|0660);
	pid=fork();
	if(pid>0){
		while(1){
		msgrcv(msqid,&msg,sizeof(msg),5,0);
		printf("\n接收到终端二的消息：%s\n",msg.buf);
		if(!strncmp("end",msg.buf,3))break;
		}
		wait(NULL);
	}
	else if(pid==0){
		while(1){
		printf("终端一请输入:");
		gets(msg.buf);
		msg.mtype=2;
		msgsnd(msqid,&msg,sizeof(msg),0);
		if(!strncmp("end",msg.buf,3))break;
		}
	}
}

