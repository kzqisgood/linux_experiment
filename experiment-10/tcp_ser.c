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
	pid_t pid;
	int sockfd,acceptfd;
	char buf[1024]={0};
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		printf("创建失败\n");
		return -1;
	}
	
	struct sockaddr_in serveraddr,clientaddr;
	socklen_t addrlen = sizeof(serveraddr);
	bzero(&serveraddr, addrlen);
	bzero(&clientaddr, addrlen);
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serveraddr.sin_port = htons(7777);
	if(bind(sockfd,(struct sockaddr *)&serveraddr,addrlen)<0)
	{
	printf("绑定失败\n");
	return -1;
	}
	if(listen(sockfd,5) < 0){
	printf("监听失败\n");
	return -1;
	}
	if((acceptfd = accept(sockfd,(struct sockaddr *)&clientaddr,&addrlen))<0)
	{
	printf("接收失败\n");
	return -1;
	}
	printf("与以下地址建立联系\n");
	printf("ip: %s, port: %d\n",inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port));
	ssize_t bytes;
	if((pid=fork())<0)
	{
	printf("进程创建失败\n");
	return -1;
	}
	if(pid==0)
	{
	while(1)
	{
	if((bytes = recv(acceptfd, buf, 128, 0)) < 0){
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
	else if(pid > 0)
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
	if(send(acceptfd, buf, 128, 0) < 0)
        {
        printf("发送失败");
        return -1;
        }
	memset(buf, 0, sizeof(buf));
	}
	}
	close(acceptfd);
	close(sockfd);
	return 0;	
	
}
