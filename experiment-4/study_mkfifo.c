#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main()
{
	char buf[1024];
	int fd;
	fd=open("FIFO",O_WRONLY);
	read(0,buf,sizeof(buf));
	write(fd,buf,sizeof(buf));
	close(fd);
}
