#include <sys/types.h>
#include <unistd.h> 
#include <signal.h>
#include <stdio.h>
//kill 发送信号
//kill(pid_t pid, int sig);
//参数pid用来设置信号发送的对象，参数sig为信号的名称
//raise 发送信号给自身
//raise(int sig);
//参数sig为信号的名称

int main()
{
	pid_t pid;
	pid = fork();
	if(pid>0)
	{
	printf("进入父进程\n");
	sleep(4);
	printf("正在杀死子进程\n");
	sleep(2);
	kill(pid,SIGKILL);
	printf("子进程已经被杀死\n");
	sleep(2);
	printf("开始杀死父进程\n");
	sleep(1);
	raise(SIGKILL);
	}
	else
	{
	while(1)
	{
	sleep(1);
	printf("我是子进程\n");
	}
	}
}
