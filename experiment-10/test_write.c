#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
int main()
{
	char buf[1024]={0};
	printf("成功\n");
	read(0,buf,sizeof(buf));
	write(1,buf,sizeof(buf));
	return 0;
}
