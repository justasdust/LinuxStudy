#include"ch07.h"
static void __attribute__((constructor))before_main(void){
	printf("---------------Before Main-----------------\n");
}
static void __attribute__((destructor))after_main(void){
	printf("---------------After Main------------------\n");
}
int main(){
	printf("               In Main\n");
	return 0;
	//exit(0);
	//_exit(0);
}
