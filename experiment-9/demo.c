#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

pthread_mutex_t lock;
int data[2];
int flage=0;
pthread_cond_t A;
pthread_cond_t B;

void thread_A(int *tmp)
{
	int i=1;
	while(1)
	{
		pthread_mutex_lock(&lock);
		if(flage==1)
			pthread_cond_wait(&A,&lock);
		data[0]=i;
		data[1]=i+1;
		printf("data[0]=%d	data[1]=%d\n",data[0],data[1]);
		flage=1;
		i++;
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
		printf("data[0]*data[1]=%d\n",data[1]*data[0]);
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
