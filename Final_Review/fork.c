#include <stdio.h>
#include <sys/types.h> 
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
int main()
{
	pid_t pid;
	pid=fork();
	if(pid>0)
	{
		int a=0;
		int b=1;
		int status;
		printf("a=%d,b=%d,a+b=%d\n",a,b,a+b);
		printf("我是父进程，我的pid=%d\n",getpid());
		
		wait(&status);
		printf("子进程的status=%d\n",status);
	}
	else
	{
		for(int i=0;i<10;i++)
			printf("我是子进程,我的pid=%d,我的ppid=%d\n",getpid(),getppid());
		exit(6);
	}
}
