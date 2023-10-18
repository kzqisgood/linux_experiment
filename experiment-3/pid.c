#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
void main(){
	int i,pid;
       for(i=0;i<2;i++){
	pid=getpid();
	if(pid>0){
		fork();
		printf("my pid=%d my ppid=%d my pgid=%d\n",getpid(),getppid(),getpgid(getpid()));
	}
	else
	printf("my pid=%d my ppid=%d my pgid=%d\n",getpid(),getppid(),getpgid(getpid()));
       }
}
