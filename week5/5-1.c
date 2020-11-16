#include"ch03.h"
int main(){
	char buf[1024];
	//printf("Hello!");
	setvbuf(stdout, buf, _IOFBF, 1024);
	printf("HELLO!");
	//设置为全缓冲

	//for(int i=0; i<1024; i++) printf(" ");
	//填满缓冲区，自动刷新
	while(1);  //默认使用行缓冲，未遇到换行符，缓冲区不刷新

	return 0;
}
