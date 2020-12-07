#include "ch12.h"
int main(){
	int fd[2];
	char buf[50];
	memset(buf, 0, sizeof(buf));
	pid_t k;
	pipe(fd);
	k = fork();
	if(k<0){
		perror("fork error!\n");
		exit(-1);
	}
	else if(k==0){
		close(fd[1]);
		sleep(1);
		int i = read(fd[0], buf, sizeof(buf));
		if(i==0){
			printf("child read failed!\n");
		}
		else{
			printf("read from pipe: %s\n", buf);
			exit(1);
		}
	}
	else{
		close(fd[0]);
		//strcpy(buf, "hello!");
		sprintf(buf, "%d say hello to %d!", getpid(), k);
		int i = write(fd[1], buf, sizeof(buf));
		if(i = 0){
			err_exit("parent write failed!\n");
		}
		else{
			printf("write from pipe: %s\n", buf);
			//exit(1);
		}
		wait(NULL);
		exit(1);
	}
	return 0;
}	
