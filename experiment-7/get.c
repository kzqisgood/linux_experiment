#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <sys/sem.h>
#include <string.h>
#include <unistd.h>

#define N 128

struct shmbuf{
	char buf[N];
};

union semun{
	int val;
};

int main(int argc, const char *argv[])
{
	key_t key;

	if ((key = ftok(".", 'q')) < 0){
		perror("ftok error");
		return -1;
	}

	int semid;
	union semun semun;
	struct sembuf sem;
	semid = semget(key, 4, IPC_CREAT | IPC_EXCL | 0664);

	if (semid < 0){
		if (errno != EEXIST){
			perror("semget error");
			return -1;
		} else {
			semid = semget(key, 2, 0664);
		}
	} else {
		/*初始化信号量的值*/
		semun.val = 0;
		semctl(semid, 0, SETVAL, semun);
		semun.val = 0;
		semctl(semid, 1, SETVAL, semun);
		semun.val = 4;
		semctl(semid, 2, SETVAL, semun);
		semun.val = 2;
		semctl(semid, 3, SETVAL, semun);
	}

	pid_t pid;
	pid=fork();

	while(1){
		if(pid==0)
		{//son
			sleep(3);
			sem.sem_num = 3;
			sem.sem_op = -1;
			sem.sem_flg = 0;
			semop(semid, &sem, 1);

			int retval;
			retval = semctl(semid, 0, GETVAL);
			if(retval != 0){
				//get apple from dish;
				sem.sem_num = 0;
				sem.sem_op = -1;
				sem.sem_flg = 0;
				semop(semid, &sem, 1);
				printf("son get an apple\n");

				sem.sem_num = 2;
				sem.sem_op = 1;
				sem.sem_flg = 0;
				semop(semid, &sem, 1);
				printf("put apple to dish\n");

			}
			printf("apple=%d dish=%d\n",semctl(semid, 0, GETVAL),semctl(semid, 2, GETVAL));

			sem.sem_num = 3;
			sem.sem_op = 1;
			sem.sem_flg = 0;
			semop(semid, &sem, 1);

		}
		else
		{//daughter
			sleep(4);
			sem.sem_num = 3;
			sem.sem_op = -1;
			sem.sem_flg = 0;
			semop(semid, &sem, 1);

			int retval;
			retval = semctl(semid, 1, GETVAL);
			if(retval != 0){
				//get orange from dish;
				sem.sem_num = 1;
				sem.sem_op = -1;
				sem.sem_flg = 0;
				semop(semid, &sem, 1);
				printf("daughter get an orange\n");

				sem.sem_num = 2;
				sem.sem_op = 1;
				sem.sem_flg = 0;
				semop(semid, &sem, 1);
				printf("put orange to dish\n");

			}
			printf("orange=%d dish=%d\n",semctl(semid, 1, GETVAL),semctl(semid, 2, GETVAL));

			sem.sem_num = 3;
			sem.sem_op = 1;
			sem.sem_flg = 0;
			semop(semid, &sem, 1);
		}
	}
}
