#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(){
	if(mkfifo("fifo",0664)<0){
	printf("mkfifo error");
	}
	int fd;
	printf("open before\n");
	if((fd=open("fifo",O_RDWR)) > 0){
		printf("fd = %d\n",fd);
	}
	printf("open after\n");
	return 0;
}
