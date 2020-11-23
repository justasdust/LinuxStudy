#include"ch10.h"
int main(int argc, char**argv){
	int i;
	printf("10-1 : pid = %d, ppid = %d\n", getpid(), getppid());
	system("./test hello world 2020 11 23");
	printf("after calling!\n");
	return 0;
}
