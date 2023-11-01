#include <stdio.h>
#include <unistd.h>
#define N 1024
int main(){
	int i,fd[2];
	int count=0;
	char buf[N]="";
	for(i=0;i<N;i++){
	buf[i]='p';
	}
	close(fd[0]);
	write(fd[1],buf,N);
	return 0;
}
