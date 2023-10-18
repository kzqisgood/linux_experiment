#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
 #include <unistd.h>
int main(){
	pid_t pid;
	int status;
	int ret;
	pid = fork();
	printf("%d %d\n",getpid(),getppid());
	if(pid==0)
	{
	sleep(1);
	printf("child=%d\n",getppid());
	exit(2);
	}
	else if(pid>0)
	{
		ret=wait(&status);
		printf("ret=%d sta=%d\n",ret,status);	
	}

}
