#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
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
	shmid = shmget(key,512,0664);
        shm = shmat(shmid,NULL,0);
	printf("a=%d b=%c \n", shm->a ,shm->b);
	shmdt(shm);
	shmctl(shmid, IPC_RMID, NULL);
	system("ipcs -m");
	return 0;
}
