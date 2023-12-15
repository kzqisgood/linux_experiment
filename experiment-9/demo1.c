#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

pthread_mutex_t lock;
char a[4];
pthread_cond_t A;
pthread_cond_t B;
int flage=0;

void thread_A(int *tmp)
{
	int i=49;
	while(1)
	{   
		pthread_mutex_lock(&lock);
		if(flage==1)
			pthread_cond_wait(&A,&lock);
		for(int j=0;j<4;j++)
		{
			a[j]=i+'0';
			i++;
			if(i==75)
				i=49;
		}
		flage=1;
		printf("write: a[0]=%c a[1]=%c a[2]=%c a[3]=%c\n",a[0],a[1],a[2],a[3]);
		pthread_cond_signal(&B);
		pthread_mutex_unlock(&lock);
		sleep(1);
	}   
}

void thread_B()
{
	while(1)
	{   
		pthread_mutex_lock(&lock);
		if(flage==0)
			pthread_cond_wait(&B,&lock);
		printf("read: a[0]=%c a[1]=%c a[2]=%c a[3]=%c\n",a[0],a[1],a[2],a[3]);
		flage=0;
		pthread_cond_signal(&A);
		pthread_mutex_unlock(&lock);
		sleep(2);
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
