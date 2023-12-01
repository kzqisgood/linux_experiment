nclude <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

void thread_A(int *tmp)
{
	int i=0;
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
	while(1)
	{
	sleep(1);
	i++;
	*tmp=i;
	}
	pthread_exit(NULL);
}

void thread_B()
{
	int i=0;
	int tmp=0;
	int *result=malloc(sizeof(int));
	for(i=0;i<1000;i++)
	{
		tmp+=i;
	}
	*result=tmp;
	printf("thread_B tmp=%d\n",*result);
	pthread_exit(result);
}

int main()
{
	pthread_t pth,pth1;
	int *ret,*tmp;
	pthread_create(&pth,NULL,(void *)thread_A,tmp);
        pthread_create(&pth1,NULL,(void *)thread_B,NULL);
	sleep(5);
	pthread_join(pth1,(void **)&ret);
	pthread_cancel(pth);
	pthread_join(pth,NULL);
	printf("*tmp=%d *ret=%d\n",*tmp,*ret);
	free(ret);
}

