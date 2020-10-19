#include"ch03.h"
int main(){
	int d1, d2;
	char buf[6];
	d1 = open("foo.txt", O_RDONLY);
	d2 = dup(d1);
	printf("fd1=%d, fd2=%d\n", d1, d2);
	lseek(d1, 5, SEEK_SET);
	read(d2, buf, 5);
	printf("%s\n", buf);

	return 0;
}
