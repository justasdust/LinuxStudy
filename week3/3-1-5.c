#include "ch02.h"
int main()
{
	int fd = open("./ftest.txt", O_RDWR);
	printf("fd = %d\n", fd);
	FILE* fp = fdopen(fd, "w+");
	fprintf(fp, "%s", "test fdopen().\n");
	fclose(fp);

	return 0;
}
