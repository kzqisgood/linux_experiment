#include <stdio.h>

int main()
{
	//fopen打开文件
	//fputc写入一个字符
	//fgetc读出一个字符
	
	//fputs写入字符串，和下面那个相比少了一个读取字符串的个数
	//返回值：
	//如果成功写入，则返回非负值。
	//如果发生错误，返回 EOF。
	
	//fgets读取字符串，参数(char *s, int size, FILE *stream);*s存储读取的字符串，size读取的字符串个数，最后一个是文件流指针
	//返回值：
	//如果成功读取，则返回 str。
	//如果到达文件末尾或发生读取错误，返回 NULL。
	
	//fread fread(const void *ptr, size_t size, size_t nmemb, FILE *stream);与下面的那个类似
	//返回值：
	//返回实际读取的数据项的数量。如果返回值小于 nmemb，则可能已经到达文件末尾或发生了错误。
	
	//fwrite按数据大小的格式写入文件fwrite(const void *ptr, size_t size, size_t nmemb,FILE *stream);
	//*ptr要写入的数据，size写入数据的大小，该值可以用sizeof()计算，注意这是实际写入的数据大小，
	//当它不满足时返回值会小于nmemb，nmemb写入数据的个数，最后一个不用解释了。
	//返回值：
	//返回实际写入的数据项的数量。如果返回值小于 nmemb，则可能发生了错误。
	FILE *fd,*fd1;//定义文件流指针
	int CHAR;
	size_t num=1,tmp_num=0;
	char buf[2]={0};
	fd=fopen("a","r+");
	fd1=fopen("a_cp","w+");
	printf("a=%p\n",fd);
	printf("a_cp=%p\n",fd1);
	while(1)
	{
		//	CHAR=fgetc(fd);
		//	if(CHAR==EOF)
		//	break;
		//	fputc(CHAR,fd1);
		//	if(fgets(buf,10,fd)==NULL)
		//	break;
		//	printf("%s",buf);
		//	fputs(buf,fd1);
		printf("开始\n");
		tmp_num=fread(buf,sizeof(buf),num,fd);
		printf("%s",buf);
		printf("tmp_num=%ld\n",tmp_num);
		if(tmp_num<1)
		break;
		fwrite(buf,sizeof(buf),num,fd1);
	}
	fclose(fd);
	fclose(fd1);
}
