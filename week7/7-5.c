#include"ch07.h"
int main(){
	extern char ** environ;
	char ** env = environ;
	int i;
	
	while(*env){
		printf("%s\n", *env);
		env++;
	}
	//printf("%s\n", getenv("PATH"));
	return 0;
}
