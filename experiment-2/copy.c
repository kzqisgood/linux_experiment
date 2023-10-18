#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <fcntl.h>
#include<unistd.h>
int main(int argc,char *argv[])
{
	if(argc<3)
		return 1;
	//open
	int fd;
	int fd1,cnt;
	char buf[1024];
	fd=open(argv[1],O_RDONLY);
	fd1=open(argv[2],O_WRONLY|O_CREAT,0666);
	printf("%d %d \n",fd,fd1);
	printf("%s\n",argv[0]);
//	cnt=read(fd,buf,sizeof(buf));
	//read write
	
	while((cnt=read(fd,buf,sizeof(buf)))>0)
	write(fd1,buf,cnt);
	printf("cnt=%d\n",cnt);
	//close
	close(fd);
	close(fd1);
}
