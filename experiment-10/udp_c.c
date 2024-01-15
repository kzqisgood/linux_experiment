#include <stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
int main()
{
	int flag_s=1,flag_r=1;
	int sockfd;
	int pid,pid_s;
	struct sockaddr_in serveraddr, clientaddr;
	socklen_t addrlen = sizeof(serveraddr);
	char buf[1024]={0};
	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
		printf("创建套接字失败\n");
		return 0;
	}
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serveraddr.sin_port = htons(7777);
	clientaddr.sin_family = AF_INET;
	clientaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	clientaddr.sin_port = htons(7778);

	if(bind(sockfd, (struct sockaddr *)&clientaddr, addrlen) < 0){
		printf("error\n");
		return 0;
	}

	ssize_t bytes;
	if((pid=fork())<0)
	{
		printf("进程创建失败\n");
		return -1;
	}
	if(pid>0)
	{
		if((pid_s=fork())<0)
		{
			printf("进程创建失败\n");
			return 0;
		}
		if(pid_s==0)
		{
			while(1)//发送子进程
			{
				read(0,buf,sizeof(buf));
				if(sendto(sockfd,buf,128,0,(struct sockaddr *)&serveraddr, addrlen) < 0){
					printf("发送失败\n");
					exit(0);
				}
				if(strncmp(buf, "quit", 4) == 0)
				{
					exit(EXIT_SUCCESS);
				}
				memset(buf, 0, sizeof(buf));//清空数组
			}
		}
		while(1)
		{
                                int status_r;
                                int status_s;
                                pid_t result = waitpid(pid,&status_r,WNOHANG);
                                pid_t result_s = waitpid(pid_s,&status_s,WNOHANG);
                                if(pid==result)
                                {
                                        kill(pid_s,SIGTERM);
                                        printf("退出发送进程\n");
                                        flag_r=0;
				printf("flag_r=%d,flag_s=%d\n",flag_r,flag_s);
                                }
                                else if(pid_s==result_s)
                                {
                                        kill(pid,SIGTERM);
                                        printf("退出接收进程\n");
                                        flag_s=0;
				printf("flag_r=%d,flag_s=%d\n",flag_r,flag_s);
                                }
                                if((flag_r==0)&&(flag_s==0))
                                { 
                                        printf("退出父进程\n");
					break;
                                }

		}
	}
	else
	{//
		while(1)
		{
			if((bytes = recvfrom(sockfd, buf, 128, 0,(struct sockaddr *)&serveraddr, &addrlen)) < 0){
				printf("接收失败\n");
				exit(0);
			}
			printf("来自以下地址的联系\n");
			printf("ip: %s, port: %d\n",inet_ntoa(serveraddr.sin_addr),ntohs(serveraddr.sin_port));
			printf("%s",buf);
			if(strncmp(buf, "quit", 4) == 0)
			{
				exit(EXIT_SUCCESS);
			}
			memset(buf, 0, sizeof(buf));
		}
	}
}
