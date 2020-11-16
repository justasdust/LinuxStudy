#include"ch09.h"
char *env_init[] = {"USER=stu", "PATH=/tmp", NULL};
int main(){
	char *args[] = {"./test", "hello", "world!\n", NULL};
	if(execve("./test", args, env_init) == -1){
		perror("execve!\n");
		exit(EXIT_FAILURE);
	}
	puts("Never get here!\n");
	exit(EXIT_SUCCESS);

	return 0;
}
