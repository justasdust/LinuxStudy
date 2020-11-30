#include"ch11.h"
int main(int argc, char**argv){
	int i;
	printf("test : pid = %d, ppid = %d\n", getpid(), getppid());
	for(int i=0; i<argc; i++){
		printf("argv[%d]: %s\n", i, argv[i]);
	}
	sleep(30);
	return 0;
}
