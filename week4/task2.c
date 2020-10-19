#include"ch03.h"
#include<malloc.h>

char* fileRead(FILE* fp, int k){
	int n;
	fread(&n, 4, 1, fp); //从文件中读取总个数
	int len[10], sum = 0;
	fread(&len[1], 4, 9, fp);
	for(int i=1; i<k; i++){
		sum += len[i];
	}	//得到前k个记录长度之和

	char* buf = (char*)malloc(len[k]);
	fseek(fp, sum+4*(n+1), SEEK_SET);
	if(fread(buf, sizeof(char), len[k], fp) != len[k])
		perror("fread error!\n");
	return buf;
}

int main(){
	int n;
	FILE* fp = fopen("task2.txt", "r");
	char* content = fileRead(fp, 1);
	printf("content 1 is \"%s\".\n", content);
	fclose(fp);
	free(content);

	return 0;
}
