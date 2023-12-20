#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int cnt,fsize;
void printpro()
{
	//printjindu
	int c;
	printf("大小=%d,当前进度=%d\n",fsize,cnt);
	if(cnt==fsize)
	{
		printf("end\n");
		c=open("c",O_RDWR|O_CREAT,0644);
		write(c,"end",3);
		close(c);
	}
}
void sentusr()
{
	kill(getppid(),SIGUSR1);
	printf("子进程执行\n");
}
int main()
{
	int pid,a,b,c;
	pid=fork();
	char buf[1024]={0};
	if(pid>0)
	{//parent
		signal(SIGUSR1,printpro);
		a=open("a",O_RDWR);
		b=open("b",O_RDWR|O_CREAT,0644);
		c=open("c",O_RDWR|O_CREAT,0644);
		fsize=lseek(a,0,SEEK_END);
		lseek(a,0,SEEK_SET);
		while(read(a,buf,1)>0)
		{
			usleep(200000);
			write(b,buf,fsize);
			cnt++;
		}
		close(a);
		close(b);
		//	wait(NULL);
		sleep(10);
		read(c,buf,3);
		if(strncmp("end",buf,3)==0)
		kill(pid,SIGINT);
		wait(NULL);
	}
	else if(pid==0)
	{//child:
		signal(SIGALRM,sentusr);
		/*		while(1)
				{
				sleep(1);
				kill(getppid(),SIGUSR1);
				}*/
		ualarm(999999,999999);
		printf("return value of ularm\n");
		while(1);
	}
}
