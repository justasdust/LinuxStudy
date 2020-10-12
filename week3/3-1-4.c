#include "ch02.h"
int main()
{
	FILE* fp = fopen("./ftest.txt", "a");
	char buf[80];
	printf("write string to ftest.txt\n");
	memset(buf, '\0', sizeof(buf));
	fread(buf, sizeof(buf), 1, stdin);
	//fgets(buf, sizeof(buf), fp);
	int ret = fwrite(buf, sizeof(buf), 1, fp);
	
	printf("File content:\n");
	fread(buf, sizeof(buf)/4, 4, fp);
	printf("%s\n\nret = %d\n", ret);
	fclose(fp);

	return 0;
}
