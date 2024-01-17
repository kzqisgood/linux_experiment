#include <stdio.h>
#include <sys/types.h> 
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>
//ftok生成一个key值
//key_t ftok(const char *pathname, int proj_id);
//参数pathname（路径名必须存在且可以自定义）与proj_id的低8位（可以自定义）
//共同产生一个key值。key值可以被msgget()函数、shmget()函数、
//semget()函数使用
//msgget创建或打开队列
//msgget(key_t key, int msgflg);
//参数msgflg用来设置标志位属性，可以指定IPC_CREAT，
//表示如果消息队列不存在，则自动创建。也可以指定IPC_EXCL，
//表示如果队列已存在，则返回错误码EEXIST。
//msgsnd发送消息
//消息添加到已经打开的消息队列的末尾。
//int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);
//参数msqid表示消息队列标识符。
//参数msgp代表添加到消息队列中的消息。
//msgp指向msgbuf的指针。
//参数msgsz表示消息正文mtext的大小。
//参数msgflg用来设置发送时的属性.
//msgrcv接收消息
//ssize_t msgrcv(int msqid, void *msgp, size_t msgsz,
// long msgtyp,int msgflg);
//消息选择性读取，0第一条
//msgctl消息的控制
//int msgctl(int msqid, int cmd, struct msqid_ds *buf);
//cmd设定对消息的控制，buf描述消息队列的各种属性信息。
#define N 128
#define SIZE sizeof(struct msgbuf) - sizeof(long)

struct msgbuf {
	long mtype;
	int a;
	char b;
	char buf[N];
};

int main()
{
	key_t key;
	key=ftok(".",'a');
	int msqid;
	struct msgbuf msg;
	msqid = msgget(key,IPC_CREAT|0644);
	msg.mtype = 100;
	msg.a = 10;
	msg.b = 'm';
	strcpy(msg.buf, "hello");
	
	msgsnd(msqid,&msg,SIZE,0);

	system("ipcs -q");
	return 0;
}
