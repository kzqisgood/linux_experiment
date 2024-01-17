#include <signal.h>
#include <stdio.h>
#include <unistd.h>
//signal()信号的注册
//sighandler_t signal(int signum, sighandler_t handler);
//signum为信号的名称,参数handler为指向信号处理函数的指针
//该函数无返回值，且参数为int类型，第一个参数信号的名称将传给第二个
//参数信号处理函数并作为其参数使用

void handler(int arg)
{
	if(arg == SIGINT)
	{
	printf("catch the SIGINT\n");
	}
}

int main()
{
	signal(SIGINT,handler);
	while(1)
	{
	sleep(1);
	printf("hello world\n");
	}
}
