#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define errlog(errmsg) perror(errmsg);\
	printf("--%s--%s--%d--\n",\
	__FILE__, __FUNCTION__, __LINE__);\
	return -1;
int main()
{
	int fd,fd1;
	const char *buf = "My ship is solid!\n";
	ssize_t nr,nr1;
//	unsigned long word;
	char word[19];
	fd = open("./tmp.txt",O_RDWR);
	printf("%d\n",fd);
	if (fd == -1)
	printf("error open\n");
	nr = write (fd,buf,strlen(buf));
	printf("%ld\n",nr);
	if (nr == -1)
		printf("error write\n");
	nr1=read(fd, word,18);
	printf("%ld\n",nr1);
		if(nr1 == -1)
		{	printf("error read\n");
			printf("%d\n",errno);
		}
		if(nr1 == nr)
		{	printf("read success\n");
			printf("%s\n",word);
		}
//		printf("%s\n",word);
	close(fd);
	return 0;
}
