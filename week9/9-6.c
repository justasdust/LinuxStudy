#include"ch09.h"

char buf[1024];
int fd_in, fd_out;

int writeTime(){
	struct timeval tv;
	struct timezone tz;
	struct tm * p;
	gettimeofday(&tv, &tz);
	p = localtime(&tv.tv_sec);
	memset(buf, 0, 1024);
	int ret = sprintf(buf,"\t create time: %d/%d/%d %d:%d:%d.%ld\n", p->tm_year+1900, 1+p->tm_mon, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec, tv.tv_usec);	
	write(fd_out, buf, strlen(buf));
	memset(buf, 0, 1024);
	return ret;
}

int main(){
	pid_t pid1, pid2;
    	
	fd_in = open(INFILE, O_RDONLY);
	if(fd_in < 0){
		fprintf(stderr, "failed to open %s, reason(%s)\n", INFILE, strerror(errno));
		return 1;
	}
	
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
		pid_t pid1_1, pid1_2;
		pid1_1 = fork();
        	if(pid1_1 < 0){
                	fprintf(stderr, "Failed to fork, reason(%s)\n", strerror(errno));
                	return 1;
        	}
        	if(pid1_1 == 0){
                	sprintf(buf, "Grandchild1 pid: %d  ppid: %d", getpid(), getppid());
			write(fd_out, buf, strlen(buf));
			writeTime();
                	exit(0);
        	}

        	pid1_2 = fork();
        	if(pid1_2 < 0){
                	fprintf(stderr, "Failed to fork, reason(%s)\n", strerror(errno));
                	return 1;
       		}
		if(pid1_2 == 0){
                	sprintf(buf, "Grandchild2 pid: %d  ppid: %d", getpid(), getppid());
			write(fd_out, buf, strlen(buf));
			writeTime();
                	exit(0);
        	}
        	if(pid1_1>0 && pid1_2>0){
                	sprintf(buf, "Child1 pid: %d  grandchild1: %d  grandchild2: %d", getpid(), pid1_1, pid1_2);
			write(fd_out, buf, strlen(buf));
			writeTime();
                	waitpid(pid1_1, NULL, 0);
                	waitpid(pid1_2, NULL, 0);
                	exit(0);
        	}
		exit(0);
	}

	pid2 = fork();
	if(pid2 < 0){
                fprintf(stderr, "Failed to fork, reason(%s)\n", strerror(errno));
                return 1;
        }
	if(pid2 == 0){
                pid_t pid2_1, pid2_2; 
                pid2_1 = fork();
                if(pid2_1 < 0){
                        fprintf(stderr, "Failed to fork, reason(%s)\n", strerror(errno));
                        return 1;
                }
                if(pid2_1 == 0){
                        sprintf(buf, "Grandchild1 pid: %d  ppid: %d", getpid(), getppid());
			write(fd_out, buf, strlen(buf));
			writeTime();
                        exit(0);
                }

		pid2_2 = fork();
                if(pid2_2 < 0){
                        fprintf(stderr, "Failed to fork, reason(%s)\n", strerror(errno));
                        return 1;
                }
                if(pid2_2 == 0){
                        sprintf(buf, "Grandchild2 pid: %d  ppid: %d", getpid(), getppid());
			write(fd_out, buf, strlen(buf));
			writeTime();
                        exit(0);
                }
		if(pid2_1>0 && pid2_2>0){
                        sprintf(buf, "Child2 pid: %d  grandchild1: %d  grandchild2: %d", getpid(), pid2_1, pid2_2);
			write(fd_out, buf, strlen(buf));
			writeTime();
                        waitpid(pid2_1, NULL, 0);
                        waitpid(pid2_2, NULL, 0);
                        exit(0);
                }
                exit(0);
	}
	if(pid1>0 && pid2>0){
		sprintf(buf, "Parent pid: %d  child1: %d  child2: %d", getpid(), pid1, pid2);
		write(fd_out, buf, strlen(buf));
		writeTime();
		waitpid(pid1, NULL, 0);
		waitpid(pid2, NULL, 0); 
		exit(0);
	}

	return 0;
}
