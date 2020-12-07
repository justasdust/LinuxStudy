#include"ch12.h"
int main(){
	char buf[1024];
	memset(buf, 0, sizeof(buf));
	pid_t fd1[2], fd2[2], p1, p2;
	pipe(fd1);
	pipe(fd2);
	p1 = fork();
	if(p1<0){
		err_exit("fork failed!\n");
	}
	else if(p1==0){
		close(fd1[0]);
		sprintf(buf, "parent= %d: %d send message!\n", getppid(), getpid());
		int i = write(fd1[1], buf, sizeof(buf));
		if(i==0) err_exit("p1 write failed!\n");
		else sleep(1);
		close(fd2[1]);
		memset(buf, 0, sizeof(buf));
		i = read(fd2[0], buf, sizeof(buf));
		if(i==0) err_exit("p1 read failed!\n");
		else printf("%d read: %s", getpid(), buf);
		exit(0);
	}
	else{
		p2 = fork();
		if(p2<0){
			err_exit("fork failed!\n");
		}
		else if(p2==0){
			sleep(1);
			close(fd1[1]);
			int i = read(fd1[0], buf, sizeof(buf));
			if(i==0) err_exit("p2 read failed!\n");
			else {
				close(fd2[0]);
				printf("%d read: %s", getpid(), buf);
				memset(buf, 0, sizeof(buf));
				sprintf(buf, "parent= %d: %d send message!\n", getppid(), getpid());
				i = write(fd2[1], buf, sizeof(buf));
				if(i==0) err_exit("p2 write failed!\n")
;
				exit(0);
			}
		}
		else{
			close(fd1[0]);
			close(fd1[1]);
			close(fd2[0]);
			close(fd2[1]);
			wait(NULL);
			wait(NULL);
			exit(0);
		}
	}
}
