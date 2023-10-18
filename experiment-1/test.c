#include<stdio.h>
int main(int argc,char *argv[])
{
	FILE *fp;
	fp=fopen("./tmp/tmpfile","w+");
	printf("%p\n",fp);
	fclose(fp);
	return 0;
}
