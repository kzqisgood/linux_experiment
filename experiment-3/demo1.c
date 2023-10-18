#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
void main(){
	int pid,pid1;
	pid = fork();
	if(pid>0)
	{
		pid1=fork();
	}
	printf("pid=%d,pid1=%d,my pid=%d,my ppid=%d,my gpid=%d\n",pid,pid1,getpid(),getppid(),getgid());
       return;
}
