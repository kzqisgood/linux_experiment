#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <stdlib.h>
//shmget 创建或打开共享内存
//int shmget(key_t key, size_t size, int shmflg);
//size 设置共享内存段的大小，shmflg设置属性
//shmat 映射内存段到虚拟地址空间上
//void *shmat(int shmid, const void *shmaddr, int shmflg);
//参数shmid为共享内存的标识符。参数shmaddr一般设置为NULL，
//表示系统将会自动在进程的虚拟地址空间选择一块合适
//的区域与共享内存段建立映射关系。
//参数shmflg设置为0时，表示共享内存区域可读写；
//返回值
//与物理地址建立映射关系的进程虚拟地址
//shmdt断开虚拟地址空间
//int shmdt(const void *shmaddr);
//参数shmaddr为映射断开之后的虚拟地址。
//shmctl 共享内存放入控制
//参数shmid为共享内存的标识符。参数cmd用来实现对共享内存的控制。
//参数buf指向的结构用来描述共享内存的属性。
struct shmbuf{
	int a;
	char b;
};
int main()
{
	key_t key;
	key=ftok(".",'q');
	int shmid;
	struct shmbuf *shm;
	shmid = shmget(key,512,IPC_CREAT|0664);
	shm = shmat(shmid,NULL,0);
	shm->a = 10;
	shm->b = 's';
	shmdt(shm);
	system("ipcs -m");
	return 0;
}
