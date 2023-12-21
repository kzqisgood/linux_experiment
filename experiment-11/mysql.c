#include<mysql/mysql.h>
#include<stdio.h>
const char data[10][1024]={"insert into student values('1','wang','18','2023-11-11','113','99','121','98')","insert into student values('2','Chen','18','2023-11-11','112','90','123','95')","insert into student values('3','li','19','2023-11-12','111','90','113','92')","insert into student values('4','ke','19','2023-11-12','102','80','107','99')","insert into student values('5','yun','18','2023-11-11','110','99','123','98')"};
int main()
{
	MYSQL mysql;
	int i;
	MYSQL_RES *resptr;
	MYSQL_ROW row;
	//connect database;
	if(mysql_init(&mysql)==NULL)
		return -1;
	if(mysql_real_connect(&mysql,"localhost","root","123456789","stu",0,NULL,0)==NULL)
	return -1;
	printf("连接成功\n");
	
	for(int i=0;i<5;i++){
	if(mysql_query(&mysql,data[i])==0)
        printf("insert %lu line!\n",(unsigned long)mysql_affected_rows(&mysql));
	}
	if(mysql_query(&mysql,"select * from student")!=0)
	return -1;
	resptr=mysql_store_result(&mysql);
	printf("select %lu lines\n",mysql_num_rows(resptr));
	mysql_data_seek(resptr,0);
	while(row=mysql_fetch_row(resptr))
	{	
		for(i=0;i<=mysql_field_count(&mysql);i++)
			printf("%s	",row[i]);
		printf("\n");
	}
	mysql_close(&mysql);
}
