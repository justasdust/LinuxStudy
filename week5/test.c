#include<stdio.h>
#include<malloc.h>
int main(){
	//char s[4];
	char *s = (char*)malloc(4);
	scanf("%s", s);

	return 0;
}
