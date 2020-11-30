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
#include <errno.h>
#include <sys/time.h>

#define INFILE "./in.txt"
#define OUTFILE "./log.dat"
#define MODE S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH

void err_exit(char *s){
        printf("%s", s);
        exit(0);
}

