#include"ch10.h"
int main(){
	int i, r1;
	r1 = fork();
	if(r1<0){
		printf("fork failed!\n");
		exit(-1);
	}
	else if(r1 == 0){
		printf("child: pid=%d, ppid=%d\n", getpid(), getppid());
		i = execle("./test", "test", "hello", "world", NULL, NULL);
	        if(i==-1){
        	        perror("execve failed!\n");
                	exit(1);
        	}
		exit(99);
	}
	else{
		int s, r;
		r = wait(&s);
		printf("10-8: pid=%d, ppid=%d, r1=%d, s1=%d\n", getpid(), getppid(), r1, WEXITSTATUS(s));
		exit(0);
	}
	printf("after calling!\n");
	return 0;

}
