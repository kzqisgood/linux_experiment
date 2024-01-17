#include <stdio.h>
#include <pthread.h>
//pthread_create()线程的创建
//int pthread_create(pthread_t *thread, const pthread_attr_t *attr
// ,void *(*start_routine) (void *), void *arg)
//thread表示线程标识符，*attr指向一个结构体，可以用来设置线程属性
//默认使用NULL就行，start_routine表示函数名，arg表示函数的参数
//注意线程退出条件
//pthread_exit()线程退出
//void pthread_exit(void *retval);
//retval线程退出的返回值
//pthread_join()等待指定thread标识的线程退出
//int pthread_join(pthread_t thread, void **retval);
//retval值等于pthread_exit的参数的值
void *thread1_handler(void *arg)
{
	printf("我是线程\n");
	pthread_exit("返回线程以退出\n");
}
int main()
{
	pthread_t thread;
	void *retval;
	int arg;
	pthread_create(&thread,NULL,thread1_handler,(void *)&arg);
	pthread_join(thread,&retval);
	printf("%s\n",(char *)retval);
	return 0;
}
