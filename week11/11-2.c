#include"ch11.h"
int main(){
	int i, pid1;
	pid1 = fork();
	if(pid1<0){
		printf("fork failed!\n");
		exit(-1);
	}
	else if(pid1 == 0){
		printf("child: pid=%d, ppid=%d\n", getpid(), getppid());
		i = execle("./test", "test", "hello", "world", NULL, NULL);
	        if(i==-1){
        	        perror("execve failed!\n");
                	exit(1);
        	}
		exit(0);
	}
	else{
		pid_t pid2;
		pid2 = fork();
		if(pid2<0){
			perror("fork failed!\n");
			exit(-1);
		}
		else if(pid2==0){
			printf("child2: pid = %d, ppid = %d, re = %d\n", getpid(), getppid(), pid2);
			for(int i=0; i<9; i++){
				printf("%d: Hello!\n", i);
			}	
			//sleep(20);
			exit(0);
		}

		else{
			int s1, r1, s2, r2;
			r1 = wait(&s1);
			r2 = wait(&s2);
			if(r1==pid1){
				printf("child1 %d is exited! exit code %d\n", r1, WEXITSTATUS(s1));
			}
			else if(r1==pid2){
				printf("child2 %d is exited! exit code %d\n", r1, WEXITSTATUS(s1));
			}
			if(r2==pid1){
                                printf("child1 %d is exited! exit code %d\n", r2, WEXITSTATUS(s2));
                        }
                        else if(r1==pid2){
                                printf("child2 %d is exited! exit code %d\n", r2, WEXITSTATUS(s2));
                        }


			if(WIFEXITED(s1))
				printf("parent: pid=%d, ppid=%d, r1=%d, s1=%d\n", getpid(), getppid(), r1, WEXITSTATUS(s1));
			else{
				printf("child process stopped with signal %d!\n", WTERMSIG(s1));
			}

			if(WIFEXITED(s2))
                                printf("parent: pid=%d, ppid=%d, r2=%d, s2=%d\n", getpid(), getppid(), r2, WEXITSTATUS(s2));
                        else{
                                printf("child process stopped with signal %d!\n", WTERMSIG(s2));
                        }
		}
		exit(0);
	}
	printf("after calling!\n");
	return 0;

}
