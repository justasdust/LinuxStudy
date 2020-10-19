#include"ch03.h"
int main(){
	FILE* fp = fopen("task2.txt", "w");
	int len[10], sum;
	len[0] = 9;
	for(int i=1; i<10; i++){
		len[i] = i+5;
		sum += len[i];
	}
	int ret1 = fwrite(len, 4, 10, fp);
	
	char buf[92] = "Stray birds of summer come to my window to sing and fly away. And yellow leaves of autumn, \0";
	//printf("%d", sum);
	int ret2 = fwrite(buf, sizeof(char), sum, fp);
	printf("写入了%d个数字  %d个字节。\n", ret1, ret2);

	return 0;
}
