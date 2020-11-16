#include"ch03.h"
int main(){
	char buf[20];
	int ret;
	FILE *fp = fopen("./tmp.txt", "w+");
	if(!fp){
		printf("Failed!\n");
		exit(-1);
	}
	ret = fwrite("123", sizeof("123"), 1, fp);
	printf("We write %s, ret is %d\n", buf, ret);

	memset(buf, 0, sizeof(buf));
	ret = fread(buf, 1, 1, fp);
	printf("We read %s, ret is %d\n", buf, ret);
	fwrite("456", sizeof("456"), 1, fp);
	fclose(fp);

	return 0;
}

