#include "ch07.h"
int main(int argc, char* argv[], char* env[]){
	/*
	if(argc<3){
		printf("参数不足！\n");
	}
	else if(argc==3){
		int x = atoi(argv[1]);
		int y = atoi(argv[2]);
		printf("%d\n", x+y);
	}
	else{
		printf("参数多余！\n");
	}*/
	for(int i=0; i<argc; i++){
		printf("argv[%d] : %s\n", i, argv[i]);
	}
	for(int i=0; env[i]; i++){
		printf("env[%d] : %s\n", i, env[i]);
	}
	return 0;
}
