#include <stdio.h> 
#include<sys/types.h> 
#include<sys/stat.h> 
#include<unistd.h> 
#include<fcntl.h> 
#include <sys/wait.h> 
int main() 
{ 
        int fd1,fd2,P1,P2; 
        char buf1[1024],buf2[1024]; 
        if(!(mkfifo("FIFO",0644))) 
                printf("success create FIFO\n"); 
        else
                printf("non't create FIFO\n");
        if(!(mkfifo("FIFO1",0644)))
                printf("success create FIFO1\n");
        else
                printf("non't create FIFO1\n");
        P1=fork();
        if(P1>0)
        {
                P2=fork();
		if(P2==0){
		while(1){
                fd1=("FIFO",O_RDONLY);
                read(fd1,buf1,sizeof(buf1));
		}
		}
		else if(P2>0){
		wait(NULL);
		wait(NULL);
		}
        }
        else if(P1==0)
        {
                while(1){
		fd2=("FIFO1",O_WRONLY);
                write(fd2,buf2,sizeof(buf2));
		}
        }
}
