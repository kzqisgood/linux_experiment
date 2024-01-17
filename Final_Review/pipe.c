#include <stdio.h>
#include <unistd.h>
#include <string.h>
//无名管道只能用于具有亲缘关系的进程之间通信(如父子进程)
//类似于单工的模式，无名管道具有固定的读端pipefd[0]与写端pipefd[1]。
//无名管道是特殊的文件可以使用文件I/O的read()函数和write()函数
//无名管道本质是一段内核空间中的内存段，
//因此不能使用lseek()函数对管道进行定位操作。
//管道操作是一次性操作，一旦读取后管道中的数据就会移除。
//管道大小是固定的，写满后继续写会阻塞
//当无名管道的读端被关闭时，从写端写入数据，管道将会破裂，进程将会退出。

int main()
{
	pid_t pid;
	int i,fd[2];
	char buf[1024]={0},buf_r[1024]={0};
	pipe(fd);
	pid=fork();
	
	if(pid>0)
	{
		while(1)
		{
		read(0,buf,10);
	//	printf("%s\n",buf);
		write(fd[1],buf,10);
		}
	}
	else
	{
		while(1)
		{
		read(fd[0],buf_r,10);
		write(1,buf_r,10);
		if(strcmp(buf_r,"quit\n")==0)
		break;
		
		}
	}
}
