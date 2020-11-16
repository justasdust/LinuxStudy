#include"ch07.h"
//作业改动要求：
//找出两个查询不一样的原因，并将其改正
//
//原因：原来的test_env是局部变量，set_env_string运行结束后该局部变量也随之消失，这时环境变量也随之修改，因此在show_env_string中查询不到test_env；而我将test_env设为静态变量，则它的生存期知道程序运行结束，因此show_env_string可以查询到，但是在程序运行结束后，该环境变量还是会消失的
static void set_env_string(void){
	static char test_env[] = "test_env=test";
	if(putenv(test_env)!=0){
		printf("Failed to put new env var!\n");
	}
	else{
		printf("1.The test_env string is %s\n", getenv("test_env"));
	}
}
static void show_env_string(void){
	printf("2.The test_env string is %s\n", getenv("test_env"));
}
int main(){
	set_env_string();
	show_env_string();
	return 0;
}
