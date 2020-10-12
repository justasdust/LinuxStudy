#include<stdio.h>

int main()
{
	FILE* fp = fopen("./ftest.txt", "a");
	fputs("Hello, it's my first modifition.\n", fp);
	fclose(fp);

	return 0;
}
