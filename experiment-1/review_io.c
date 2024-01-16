#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
//open 打开文件
//int open(const char *pathname, int flags); 
//int open(const char *pathname, int flags, mode_t mode);
//pathname路径，flags标志位，mode权限，仅在标志位指定了O_CREAT时使用
//返回值
//文件描述符
//write 像文件中写入
//ssize_t write(int fd, const void *buf, size_t count);
//fd文件描述符，buf要写入的数据，count要从buf中写入到文件中数据的个数
//返回值
//返回实际写入的数据个数，-1时表示发生了错误
//read 向文件中读取
//ssize_t read(int fd, void *buf, size_t count);
//返回值
//返回实际读取的字节数。如果返回值为 0，表示已经到达文件末尾。如果返回值为 -1，表示发生错误。
int main(int argc,char *argv[])
{
	int fd,fd1;
	char buf[1024]={0};
	if(argc < 3)
	{
		printf("请输入正确的输入文件的路径和输出文件的路径\n");
		return 1;
	}
	fd=open(argv[1],O_RDWR);
	fd1=open(argv[2],O_RDWR|O_CREAT,0644);
	while(read(fd,buf,1))
	{
		write(fd1,buf,1);
	}
	close(fd);
	close(fd1);
	return 0;
}
