#include <stdio.h>
#include <signal.h>
#include <unistd.h>
int main()
{
	int pid;

	pid=fork();

	if(pid==0)
	{
		printf("child");
	}
	else
	{
		sleep(1);
		kill(pid,SIGKILL);
		raise(SIGKILL);
	}
}
