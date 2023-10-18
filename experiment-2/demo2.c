#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <fcntl.h>
#include<unistd.h>
int main()
{
	int fd,flags;
	char buf[]="这是追加的内容！\n",buf1[]="这是打开时输入的内容！\n";
	fd=open("./work/systemfile",O_RDWR|O_CREAT,0640);//可读可写方式打开，不存在时创建，权限为当前用户可读可写，组用户可读
	write(fd,buf1,strlen(buf1));//打开写入
	if(fd==-1)//判断是否打开
        {       printf("文件打开失败！\n");
                return 0;
        }
	flags = fcntl(fd, F_GETFL);//获取1中的文件systemfile打开方式
	flags = O_APPEND;
	fcntl(fd, F_SETFL, flags);//设置该文件的打开方式为O_APPEND
	write(fd,buf,strlen(buf));//追加写入测试
	close(fd);//关闭文件
}
