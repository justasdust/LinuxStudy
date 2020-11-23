#include"ch10.h"
void foo(){
	fprintf(stderr, "foo says bye.\n");
}
void bar(){
	fprintf(stderr, "bar says bye.\n");
}
int main(int argc, char** argv){
	atexit(foo); //注册函数
	atexit(bar);
	fprintf(stdout, "Oops --- forgot a newline!\n");
	sleep(2);
	if(argc>1 && strcmp(argv[1], "exit")==0){
		exit(0); //清空缓冲区
	}
	if(argc>1 && strcmp(argv[1], "_exit")==0){
		_exit(0);  //不清空缓冲区，也不调用注册函数
	}
	
	return 0;
}
