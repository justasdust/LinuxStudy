#include "ch12.h"
int main(){
	int fd[2], fd2[2];
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
		close(fd2[0]);
		sleep(1);
		int i = read(fd[0], buf, sizeof(buf));
		if(i==0){
			printf("child read failed!\n");
		}
		else{
			printf("%d read from pipe %d: %s\n", getpid(), fd[0], buf);
			int n = strlen(buf);
			sprintf(buf, "I receive %d bytes from you.", n);
			int j = write(fd2[1], buf, sizeof(buf));
			if(j==0){
				printf("child write failed!\n");
			}
			else{
				printf("%d write from pipe %d: %s\n", getpid(), fd2[1], buf);
			}
			exit(0);
		}
	}
	else{
		close(fd[0]);
		close(fd2[1]);
		//strcpy(buf, "hello!");
		sprintf(buf, "%d say hello to %d!", getpid(), k);
		int i = write(fd[1], buf, sizeof(buf));
		if(i == 0){
			err_exit("parent write failed!\n");
		}
		else{
			printf("%d write from pipe %d: %s\n", getpid(), fd[1], buf);
			//exit(1);
		}
		wait(NULL);
		int j = read(fd2[0], buf, sizeof(buf));
		if(j==0){
			printf("parent read failed!\n");
		}
		else{
			printf("%d read from pipe %d: %s\n", getpid(), fd2[0], buf);
		}
		exit(1);
	}
	return 0;
}	
