//本程序测试僵尸进程（执行后再开窗口命令ps ax      cat /proc/进程号/status）
#include"ch10.h"
int main(){
	pid_t pid;
	pid = fork();
	
	if(pid<0){
		perror("error fork!\n");
		exit(1);
	}
	else if(pid==0){
		exit(0);
	}
	else{
		sleep(300);
		wait(NULL);
	}
	return 0;
}

