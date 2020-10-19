#include "ch02.h"
int main()
{
	FILE* fp;
        if((fp = fopen("./ftest.txt", "r"))==NULL){
		perror("fopen() failed.");
	}

	fp = freopen("./ftest.txt", "a+", stdout);
	printf("%s", "test freopen().\n");
	fclose(fp);

	return 0;
}
