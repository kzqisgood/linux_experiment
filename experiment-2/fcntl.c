#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
int main()
{
	int flags,file,buf[1024]={0},file1;
	file=open("./d",O_RDWR|O_CREAT);
	printf("file=%d\n",file);
	close(1);
//	read(file,buf,12);
	fcntl(file,F_DUPFD,1);
	printf("file=%d\n",file);
//	file1=open("./d1",O_RDWR|O_CREAT);
	close(file);
}
