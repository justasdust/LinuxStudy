#include"ch03.h"
#include"myfun.c"

int main(){
	usernode x;
	FILE* fp = fopen("./user.dat", "a+");
	if(!fp){
		err_exit("File open failed!\n");}
	printf("Do you want to add a record?(y/n)\n");
	char c = getchar();
	while(c=='y' || c=='Y'){
		save(fp);
		printf("Continue to append?(y/n)\n");
		//fflush(stdin);
		getchar();
		c = getchar();
		printf("%c\n", c);
	}
	rewind(fp);
	myWrite(fp);

	usersort(fp);

	fclose(fp);

	return 0;
}
