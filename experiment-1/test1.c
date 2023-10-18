#include<stdio.h>
int main(int argc,char *argv[])
{

	FILE * file;
	FILE * file1;
	FILE * file2;
	char ch;
	int cnt;
	char buf[12];
	if(argc<4)
	{
		printf("please input more 2 para\n");
		return 1;
	}
	file=fopen(argv[1],"r");
	file1=fopen(argv[2],"w+");
	file2=fopen(argv[3],"a");
	//copy:read file ,write file1
/*	while((ch=fgetc(file))!=EOF)
	{
	fputc(ch,file1);
	}
	while(fgets(buf,12,file)!=NULL)
	fputs(buf,file1);*/
	while((cnt=fread(buf,1,12,file))>0)
	{
		printf("%d\n",cnt);
	fwrite(buf,1,cnt,file1);
	fwrite(buf,1,cnt,file2);
	}

	fclose(file);
	fclose(file1);
	fclose(file2);
	return 0;
}
