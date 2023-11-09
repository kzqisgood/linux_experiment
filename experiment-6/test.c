#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
int main()
{
	int msqid,pid;
	struct msqid_ds buf;
	struct msgbuf{
		long mtype;
		char buf[1024];
	}msg;
	msqid=msgget(123,IPC_CREAT|0660);
	pid=fork();
		if(pid>0){
			while(1)
			{
			printf("终端二请输入:");
			gets(msg.buf);
			msg.mtype=5;
			msgsnd(msqid,&msg,sizeof(msg),0);
			if(!strncmp("end",msg.buf,3))break;
			}
			wait(NULL);
		}
		else if(pid==0)
		{
			while(1)
			{
			printf("接收到终端一的消息：");
			msgrcv(msqid,&msg,sizeof(msg),2,0);
			if(!strncmp("end",msg.buf,3))break;
			printf("%s\n",msg.buf);
			}
		}
}
