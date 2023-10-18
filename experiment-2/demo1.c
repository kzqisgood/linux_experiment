#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <fcntl.h>
#include<unistd.h>
int main()
{
	int fd,cnt;
	char buf[1024]="Beginning Linux Programming\n";
	fd=open("./work/systemfile",O_RDWR|O_CREAT,0640);//可读可写方式打开，不存在时创建，权限为当前用户可读可写，组用户可读
	if(fd==-1)//判断是否打开
	{	printf("文件打开失败！");
		return 0;
	}
	write(fd,buf,strlen(buf));//写入
	lseek(fd,-10,SEEK_END);//移动指针至距离结尾前10的位置
	for(int i=0;i<5;i++)//打印五个空格
		write(fd," ",1);
	close(fd);//关闭文件
         fd=open("./work/systemfile",O_RDWR|O_APPEND);//可读可写追加方式打开 提问：为什么这里不加上可读可写方式就无法追加？
         if(fd==-1)//判断是否打开
         {       printf("文件打开失败！");
                 return 0;
         }
	 write(fd,"Third Edition\n",14);//写入字符 提问：为什么这里写16会报错？15是如何计算的？第三个参数如何计算？
	close(fd);
}
