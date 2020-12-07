#include "ch12.h"
#define PIPE_BUF 1024
int main(){
	int pid, fd[2], len;
	char buffer[PIPE_BUF];
	memset(buffer, 0, sizeof(buffer));
	FILE* stream;
	if(pipe(fd) != 0)
		err_exit("pipe creation failed");
	if((pid=vfork())==0){
		int i = read();
		/*close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
		if(execl("./test", "test", NULL, NULL) == -1)
			err_exit("Unable to run test");*/
	}
	else{
		close(fd[1]);
		//printf("you can type a line and the line will echoed:\n");
		//dup2(fd[0], 0);
		int i = read(fd[0], buffer, sizeof(buffer));
		close(fd[0]);
		//while(fgets(buffer, PIPE_BUF, stdin) != NULL)
		//	puts(buffer);
		if(i==0) err_exit("read failed!\n");
		else{
			printf("%s", buffer);
		}
	}
}
