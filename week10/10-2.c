#include"ch10.h"
int main(){

	//char *argv[] = {"./test", "hello", "world", NULL};
	char *path = "/home/stitch/code/week10/test"
	printf("10-2: pid=%d, ppid=%d\n", getpid(), getppid());
	int i;
	i = execle("./test", "test", "hello", "world", NULL, NULL);
	if(i==-1){
		perror("execve failed!\n");
		exit(1);
	}
	printf("after calling!\n");
	return 0;

}
