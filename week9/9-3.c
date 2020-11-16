#include "ch09.h"

int g = 0;
int main(){
	pid_t pid;
	int l = 99;
	pid = vfork();
	if(pid < 0){
		perror("Fork failed!\n");
		exit(-1);
	}
	else if(pid == 0){
		printf("Child : ppid = %d, pid = %d\n", getppid(), getpid());
		printf("Child : init g = %d, l = %d\n", g, l);
		g--;
		l++;
		printf("Child : g = %d, l = %d\n", g, l);
		_exit(0);
		//return 0;
	}
	else{
		wait(NULL);
		printf("Parent : child pid = %d, pid = %d\n", pid, getpid());
		printf("Parent : init g = %d, l = %d\n", g, l);
                g++;
                l--;
		printf("Parent : g = %d, l = %d\n", g, l);
	}

	return 0;
}
