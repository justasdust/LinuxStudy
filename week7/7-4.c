#include"ch07.h"
static void __attribute__((constructor))before_main(){
	printf("------------Before Main------------\n");
}
static void __attribute__((destructor))after_main(){
        printf("------------After Main------------\n");
}

void callback1(){
	printf("------------CALLBACK1-------------\n");
}
void callback2(){
        printf("------------CALLBACK2-------------\n");
}
void callback3(){
        printf("------------CALLBACK3-------------\n");
}

int main(){
	while(1){
		printf("------------Running now-------------\n");
		sleep(5);
	}
	printf("------------Program Finished-------------\n");
	atexit(callback1);
	atexit(callback2);
	atexit(callback3);
}
