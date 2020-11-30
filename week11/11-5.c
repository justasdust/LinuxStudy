#include"ch11.h"

char buf[1024];
int fd_out;

int writeTime(){
	struct timeval tv;
	struct timezone tz;
	struct tm * p;
	gettimeofday(&tv, &tz);
	p = localtime(&tv.tv_sec);
	memset(buf, 0, 1024);
	int ret = sprintf(buf,"\t stop time: %d/%d/%d %d:%d:%d.%ld\n", p->tm_year+1900, 1+p->tm_mon, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec, tv.tv_usec);	
	write(fd_out, buf, strlen(buf));
	memset(buf, 0, 1024);
	return ret;
}

int main(){
	pid_t pid1, pid2;

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
		pid_t pid1_1;
		pid1_1 = fork();
        	if(pid1_1 < 0){
                	fprintf(stderr, "Failed to fork, reason(%s)\n", strerror(errno));
                	return 1;
        	}
        	else if(pid1_1 == 0){
                	sprintf(buf, "Grandchild1 pid: %d  ppid: %d", getpid(), getppid());
			write(fd_out, buf, strlen(buf));
			writeTime();
                	exit(0);
        	}
        	else{
			waitpid(pid1_1, NULL, 0);
                	sprintf(buf, "Child1 pid: %d  grandchild1: %d", getpid(), pid1_1);
			write(fd_out, buf, strlen(buf));
			writeTime();                	
                	exit(0);
        	}
		exit(0);
	}

	else{
		pid2 = fork();
		if(pid2 < 0){
                	fprintf(stderr, "Failed to fork, reason(%s)\n", strerror(errno));
                	return 1;
        	}
		else if(pid2 == 0){
                	pid_t pid2_1; 
                	pid2_1 = fork();
                	if(pid2_1 < 0){
                        	fprintf(stderr, "Failed to fork, reason(%s)\n", strerror(errno));
                        	return 1;
                	}
                	else if(pid2_1 == 0){
                        	sprintf(buf, "Grandchild2 pid: %d  ppid: %d", getpid(), getppid());
				write(fd_out, buf, strlen(buf));
				writeTime();
                        	exit(0);
                	}
			else{
				waitpid(pid2_1, NULL, 0);
                        	sprintf(buf, "Child2 pid: %d  grandchild2: %d", getpid(), pid2_1);
				write(fd_out, buf, strlen(buf));
				writeTime();
                        	exit(0);
                	}
                	exit(0);
		}
		else{
			waitpid(pid1, NULL, 0);
			waitpid(pid2, NULL, 0);
			sprintf(buf, "Parent pid: %d  child1: %d  child2: %d", getpid(), pid1, pid2);
			write(fd_out, buf, strlen(buf));
			writeTime();
			exit(0);
		}
	}

	return 0;
}
