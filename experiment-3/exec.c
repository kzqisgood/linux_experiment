#include <stdio.h>
#include <unistd.h>
#include <errno.h>
int main(){
	int ret;
	ret = execl("/bin/vi","vi","/home/wangzhang/c_study/experiment-3/txt",NULL);
	if (ret == -1)
		perror("execl");
}
