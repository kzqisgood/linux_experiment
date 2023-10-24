#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int main()
{
	pid_t pid;
	int fd[2];
	char buf[1024];
	pipe(fd);
	pid=fork();
	if(pid==0)
	{
		read(fd[0],buf,sizeof(buf));
		printf("%s\n",buf);
	}
	else if(pid>0)
	{
		write(fd[1],"123456",7);
		sleep(1);
	}
}
