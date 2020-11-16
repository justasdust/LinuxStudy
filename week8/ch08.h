#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <setjmp.h>
#include <wait.h>
#include <malloc.h>
void err_exit(char *s){
	printf("%s", s);
	exit(0);
}
