#include"ch08.h"
#include<malloc.h>
long cnt = 1024*1024;
long x = 1024;
int main(){

	void* pt=malloc(cnt);
	do{
		free(pt);
		cnt += x;
		pt = malloc(cnt*1024);
		if(pt==NULL) {
			if(x==0) break;
			else x/=10;
		}
		//printf("size: %dB\n", cnt);

	}while(1);
	printf("max: %ldKB\n", cnt);

	return 0;
}
