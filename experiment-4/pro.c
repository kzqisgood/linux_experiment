#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include <sys/wait.h>
#include <string.h>

int main()
{
	pid_t pid,pid1;
	char buf[1024];
	int fd,cnt;
	pid=fork();
	if(access("FIFO1",F_OK)!=0)
	mkfifo("FIFO1",0644);
	if(access("FIFO2",F_OK)!=0)
	mkfifo("FIFO2",0644);
	if(pid>0)
	{
		fd=open("FIFO1",O_WRONLY);
		pid1=fork();
		if(pid1==0)
		{
		while(1)
		{
		read(0,buf,sizeof(buf));
                if(strncmp(buf,"quit",4)==0)
                break;
		write(fd,buf,sizeof(buf));
		}
		}
		else if(pid1>0)
		{
		wait(NULL);
		wait(NULL);
		}
	}
	else if(pid==0)
	{
		cnt=open("FIFO2",O_RDONLY);
		while(1)
		{
		read(cnt,buf,sizeof(buf));
		if(strncmp(buf,"quit",4)==0)
		break;
		printf("pro1=%s",buf);
		}
	}
}
