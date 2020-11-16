#include"ch07.h"
#include<dlfcn.h>
extern void dynamic_lib_call(void);
int main(){
	void *handle = NULL;
	char *myso = "./libdlib.so";
	if((handle = dlopen(myso, RTLD_NOW)) == NULL){
		printf("dlopen - %s\n", dlerror());
		exit(-1);
	}
	else{
		dynamic_lib_call();
	}
	return 0;
}
