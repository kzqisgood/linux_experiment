#include <stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
int main()
{
	pid_t pid;
	ssize_t bytes;
        int sockfd;
        char buf[1024]={0};
        if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){ 
                printf("创建失败\n");
                return -1; 
        }
	struct sockaddr_in clientaddr,serveraddr;
	socklen_t addrlen = sizeof(serveraddr);
        bzero(&clientaddr, addrlen);
	bzero(&serveraddr,addrlen);
        serveraddr.sin_family = AF_INET;
        serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
        serveraddr.sin_port = htons(7777);
	clientaddr.sin_family = AF_INET;

	if(bind(sockfd,(struct sockaddr *)&clientaddr,addrlen)<0)
        {   
        printf("绑定失败\n");
        return -1; 
        }
	if(connect(sockfd, (struct sockaddr *)&serveraddr, addrlen) < 0)
	{
	printf("连接失败\n");
        return -1;
	}
	if((pid=fork())<0)
        {
        printf("进程创建失败\n");
        return -1;
        }
	if(pid>0)
	{
	int status;
	while(1)
	{
        pid_t result = waitpid(pid,&status,WNOHANG);
        if(result == -1)
	{
	printf("进程错误\n");
	return 0;
	}
	else if (result != 0)
	{
	break;
	}
	read(0,buf,sizeof(buf));
	if(send(sockfd, buf, 128, 0) < 0)
	{
	printf("发送失败");
	return -1;
	}
	memset(buf, 0, sizeof(buf));
	}
	}
	else
	{
	while(1)
	{
	if((bytes = recv(sockfd, buf, 128, 0)) < 0){
        printf("接收错误\n");
        }
        if(strncmp(buf, "quit", 4) == 0)
        {
        exit(EXIT_SUCCESS);
        }
        printf("%s",buf);
	memset(buf, 0, sizeof(buf));
	}
	}
	close(sockfd);
	return 0;
	
}
