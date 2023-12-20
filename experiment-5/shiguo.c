#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/wait.h>



int count=0; 
int file_size; 
void sig_alarm(int arg); 
void sig_usr(int sig); 

int main(int argc,char *argv[])
{
       pid_t pid;
       int i;
       int fd_src,fd_des;
       char buf[128];
       
       if(argc!=3)
       {
              printf("Pls check command format");
              return -1;
       }
       if((fd_src=open(argv[1],O_RDONLY))==-1)
       {
              perror("Open source file failed!");
              return -1;
       }
       file_size = lseek(fd_src,0,SEEK_END);
       lseek(fd_src,0,SEEK_SET);
       if((fd_des = open(argv[2],O_RDWR | O_CREAT,0644))==-1)
       {
              perror("Open target file failed!");
              return -1;
       }
       if((pid = fork()) == -1)
       {
              perror("Create process failed");
              return -1;
       }
       else if(pid > 0)//in father process
       {     signal(SIGUSR1, sig_usr);
             //sigset_t set;
             //sigemptyset(&set);
             //sigaddset(&set, SIGUSR1);
            // sigprocmask(SIG_BLOCK, &set, NULL); // 阻塞SIGUSR1信号

                  // 等待子进程发送SIGUSR1信号
             //sigfillset(&set);
             //sigdelset(&set, SIGUSR1);
             //sigsuspend(&set);

              do
              {
                        memset(buf,'\0',128);
                        if((i=read(fd_src,buf,1))==-1)
                        {
                        
                        
                              perror("Read file failed");
                              return -1;
                        }
                        else if(i==0)
                        {
                              kill(pid,SIGINT);
                              break;
                        }
                        else
                        {
                               if(write(fd_des,buf,i)==-1)
                                {
                                         perror("Write file failed");
                                         return -1;
                                }
                                count+=i;

                        }
               }
               while(i!=0);
               wait(NULL);
               exit(EXIT_SUCCESS);
             }
       else if(pid == 0)//in child process
{
   // signal(SIGUSR1, SIG_IGN); // 忽略SIGUSR1信号，避免在文件拷贝之前接收到信号
//    pause(); // 子进程暂停等待父进程发送SIGUSR1信号

    signal(SIGALRM, sig_alarm);
    ualarm(999999, 999999);
    
    while(1)
    {
        pause(); // 子进程继续等待信号，避免占用CPU资源
    }
   
    exit(EXIT_SUCCESS);
}

}
void sig_alarm(int arg)
{
      kill(getppid(),SIGUSR1);
}
void sig_usr(int sig)
{
      float i;
      i=(float)count/(float)file_size;
      printf("Copy finished: %0.0f%%\n",i*100);
}  


