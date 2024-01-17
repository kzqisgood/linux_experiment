#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/sem.h>
//semget创建或打开信号量集
//int semget(key_t key, int nsems, int semflg);
//参数nsems设置信号量集的个数，semflg设置属性
//函数执行成功就返回信号量集的标识符
//semctl信号量集控制（初始化，删除等）
//semctl(int semid, int semnum, int cmd, ...);
//参数semid表示信号量集的标识符。参数semnum表示操作的信号量的编号
//参数cmd表示对信号量的操作。
//semop PV操作(申请信号量，释放信号量)
//int semop(int semid, struct sembuf *sops, unsigned nsops);
//参数nsops表示本次将操作信号量的个数；
//参数sops则指向一个结构，该结构用来设置信号量的PV操作
/*
struct sembuf{
unsigned short sem_num;  信号量的编号    
short          sem_op;   信号量执行操作 
	大于零表示释放信号量，小于零表示申请信号量
short          sem_flg;  信号量操作标志 一般设为0
}
*/


