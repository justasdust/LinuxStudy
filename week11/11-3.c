#include "ch11.h"
//使用fork,exec,wait来测试system函数
int main()
{
        pid_t pid1;
        pid1=fork();
        if(pid1<0)
        {
            perror("fork failed!!\n");
            exit(-1);
        }
        else if(pid1==0)
        {
            char *argv[]={"./test","hello","world",NULL};
            printf("child1 :pid = %d,ppid =%d ,re=%d\n",getpid(),getppid(),pid1);
            execve("./test",argv,NULL);

            exit(0);
             
        }
		else
        {
            pid_t pid2;
            pid2=fork();
            if(pid2<0)
            {
                perror("fork failed!!\n");
            }
            else if(pid2==0)
            {
                printf("child2 :pid = %d,ppid =%d ,re=%d\n",getpid(),getppid(),pid2);
                int i;
				while(1);
                                //printf("%d :HEllo!\n",i++);
                exit(0);

            }
            else
            {
                int s1,r1,s2,r2,s3,r3;
                //r1=wait(&s1);
                r1=waitpid(pid1,&s1,0);
                r2=waitpid(pid2,&s2,WNOHANG);
                //r2=wait(&s2);
                //r3=wait(&s3);

                if(WIFEXITED(s1))//正常退出
                {
                	printf("child 1 exit normally! exit code = %d",WEXITSTATUS(s1));
				}
                else
                {
                    printf("child 1 process abnomaly! stoped with signal %d!!\n",WTERMSIG(s1));
                }

                if(WIFEXITED(s2))//正常退出
                {
	                printf("child 2 exit normally! exit code = %d",WEXITSTATUS(s1));
                }
                else
                {
       				printf("child 2 process abnomaly! stoped with signal %d!!\n",WTERMSIG(s2));
                }

                return 0;

            }


            return 0;
                //wait(NULL);
        }
}

