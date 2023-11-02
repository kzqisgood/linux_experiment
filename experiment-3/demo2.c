#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
void main(){
        int pid,pid1,status;
        pid = fork();//创建一个新进程并用pid存储返回值
        if(pid>0)	//进入父进程
        {
	       	pid1=fork();	//创建一个新进程并用pid1存储返回值
		if(pid1 == 0)	//进入打印子进程
		{
        		printf("打印子进程信息 pid=%d,pid1=%d,my pid=%d,my ppid=%d,my gpid=%d\n",pid,pid1,getpid(),getppid(),getgid());
			execl("/bin/ls","ls","-l",NULL);	//打印子进程执行该程序
		}
		waitpid(pid,&status,0);	//父进程阻塞等待暂停子进程
		printf("暂停进程的信息	pid=%d	status=%d\n",pid,status);
		printf("父进程信息 pid=%d,pid1=%d,my pid=%d,my ppid=%d,my gpid=%d\n",pid,pid1,getpid(),getppid(),getgid());
        }else if(pid == 0)	//进入阻塞子进程
	{
        	printf("暂停子进程信息 pid=%d,pid1=%d,my pid=%d,my ppid=%d,my gpid=%d\n",pid,pid1,getpid(),getppid(),getgid());
		sleep(5); //阻塞5秒
		printf("子进程结束阻塞！\n");
		exit(0);
	}
       return;
}

