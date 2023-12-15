#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

pthread_mutex_t lock;
char a[4];
pthread_cond_t A;
pthread_cond_t B;
int flage[4]={0};

void thread_A()
{
	int i=49,k=0,tmp[4]={0};//tmp标记当前可以写入数据的数组
	int sum=0;//计算当前可以写入的数据个数
	while(1)
	{   
		pthread_mutex_lock(&lock);
		for(k=0;k<4;k++)
		{
		if(flage[k]==0)
		tmp[k]=1;
		sum+=tmp[k];
		}
                if(sum==0)
                pthread_cond_wait(&A,&lock);
		sum=0;
		if(i==75)
		i=49;
		for(k=0;k<4;k++)
		{
		if(tmp[k]==0)
		continue;
		a[k]=i+'0';
		i++;
		if(i==75)
		i=49;
		flage[k]=1;
		printf("write: a[%d]=%c\n",k,a[k]);
		tmp[k]=0;
		}
		sum=0;
		pthread_cond_signal(&B);
		pthread_mutex_unlock(&lock);
		sleep(1);
	}   
}

void thread_B()
{
	int k=0,tmp[4]={0};//标记当前可以读取数据对应的数组
	int sum=0;//计算当前可以读取的数据个数
	while(1)
	{   
		pthread_mutex_lock(&lock);
		for(k=0;k<4;k++)
		{
		if(flage[k]==1)
		tmp[k]=1;
		sum+=tmp[k];
		}
                if(sum ==0 )
                pthread_cond_wait(&B,&lock);
		for(k=0;k<4;k++)
		{
		if(tmp[k])
		printf("read: a[%d]=%c\n",k,a[k]);
		flage[k]=0;
		tmp[k]=0;
		}
		pthread_cond_signal(&A);
		pthread_mutex_unlock(&lock);
		sleep(2);
		sum=0;
	}
}

int main()
{

	pthread_t pth,pth1;
	int *ret,*tmp;
	pthread_mutex_init(&lock, NULL);
	pthread_create(&pth,NULL,(void *)thread_A,NULL);
	pthread_create(&pth1,NULL,(void *)thread_B,NULL);
	pthread_join(pth,NULL);
	pthread_join(pth1,NULL);
	pthread_mutex_destroy(&lock);
	pthread_cond_destroy(&A);
	pthread_cond_destroy(&B);
	return 0;

}
