//#include <sys/types.h>
//#include <sys/stat.h>
//#include <unistd.h>
#include <fcntl.h>
//#include <stdio.h>

int main(){
	int fd = open("./test.txt", O_CREAT, 0644, "test","ver2");
	printf("file descriptor = %d \n", fd);
	close(fd);

	return 0;
}
