/*父进程派生2子进程，让它俩采用服务器转发方式通信，父进程负责记录和转发。*/
#include"ch12.h"
#define BUF_SIZE 1024

char buf[BUF_SIZE];
int fd_out;

int writeTime(pid_t pid){
	struct timeval tv;
	struct timezone tz;
	struct tm * p;
	gettimeofday(&tv, &tz);
	p = localtime(&tv.tv_sec);
	memset(buf, 0, sizeof(buf));
	int ret = sprintf(buf,"Time: %d/%d/%d %d:%d:%d.%ld\tPid: %d\tMessage: ", p->tm_year+1900, 1+p->tm_mon, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec, tv.tv_usec, pid);	
	write(fd_out, buf, strlen(buf));
	return ret;
}

int main(){
	pid_t pid1, pid2;
	char bf1[BUF_SIZE], bf2[BUF_SIZE];
	int fr1[2], fr2[2], fw1[2], fw2[2], re1, re2;
	pipe(fr1);pipe(fr2);pipe(fw1);pipe(fw2);

	fd_out = open(OUTFILE, O_WRONLY|O_CREAT|O_TRUNC, MODE);
	if(fd_out < 0){
		fprintf(stderr, "failed to open %s, reason(%s)\n", OUTFILE, strerror(errno));
		return 1;
	}	

	pid1 = fork();
	if(pid1 < 0){
		fprintf(stderr, "Failed to fork, reason(%s)\n", strerror(errno));
		return 1;
	}
	if(pid1 == 0){		
   		close(fr1[0]);close(fw1[1]);
		close(fr2[0]);close(fr2[1]);
		close(fw2[0]);close(fw2[1]);
		do{
			memset(bf1, 0, sizeof(bf1));
			memset(bf2, 0, sizeof(bf2));
			fflush(stdin);
			printf("P1: enter to send message-> ");
			fgets(bf2, sizeof(bf2), stdin);
                        re2 = write(fr1[1],bf2, strlen(bf2));
			if(re2==0) 
				perror("P1 write failed!\n");
			
			re1 = read(fw1[0], bf1, sizeof(bf1));
                        if(re1!=0)
                                printf("Message from P2: %s", bf1);
                        else
                                perror("P1 read failed!\n");
		}while(strcmp(bf2, "88\n") != 0);
		exit(0);
	}
	else{
		pid2 = fork();
		if(pid2 < 0){
                	fprintf(stderr, "Failed to fork, reason(%s)\n", strerror(errno));
                	return 1;
        	}
		else if(pid2 == 0){
			close(fr2[0]);close(fw2[1]);
			close(fr1[0]);close(fr1[1]);
	                close(fw1[0]);close(fw1[1]);
                	do{
                        	memset(bf1, 0, sizeof(bf1));
                        	memset(bf2, 0, sizeof(bf2));
				re1 = read(fw2[0], bf1, sizeof(bf1));
                                if(re1!=0)
                                        printf("Message from P1: %s", bf1);
                                else
                                        perror("P2 read failed!\n");

                        	fflush(stdin);
                        	printf("P2: enter to send message-> ");
				fgets(bf2, sizeof(bf2), stdin);
                        	re2 = write(fr2[1],bf2, strlen(bf2));
                        	if(re2==0)
                                	perror("P2 write failed!\n");
                	}while(strcmp(bf2, "88\n") != 0);
                	exit(0);
		}
		else{
			close(fr1[1]);close(fw1[0]);
			close(fr2[1]);close(fw2[0]);
			sleep(1);
			int re3, re4, flag1, flag2;
			do{
				if((flag1=waitpid(pid1, (int*)0, WNOHANG)) == 0){
					memset(bf1, 0, sizeof(bf1));
					re1 = read(fr1[0], bf1, sizeof(bf1));
					if(re1!=0){
						writeTime(pid1);
						write(fd_out, bf1, strlen(bf1));

						re2 = write(fw2[1], bf1, sizeof(bf1));
						if(re2==0)
							perror("P1 message send failed by parent!\n");
					}
					else
						perror("Parent read failed!\n");
				}
				if((flag2=waitpid(pid2, (int*)0, WNOHANG)) == 0){
                                        memset(bf2, 0, sizeof(bf2));
                                        re1 = read(fr2[0], bf2, sizeof(bf2));
                                        if(re1!=0){
                                                writeTime(pid2);
                                                write(fd_out, bf2, strlen(bf2));

                                                re2 = write(fw1[1], bf2, sizeof(bf2));
                                                if(re2==0)
                                                        perror("P2 message send failed by parent!\n");
                                        }
                                        else
                                                perror("Parent read failed!\n");
                                }	
			}while(flag1==0 || flag2==0);
			
			//waitpid(pid1, NULL, 0);
                        //waitpid(pid2, NULL, 0);
			exit(0);
		}
	}

	return 0;
}
