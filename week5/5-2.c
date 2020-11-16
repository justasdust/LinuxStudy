#include"ch03.h"
int main(){
	char buf[BUFSIZ];
	setvbuf(stdout, buf, _IONBF, BUFSIZ);
	printf("HELLO");
	while(1);

	return 0;
}
