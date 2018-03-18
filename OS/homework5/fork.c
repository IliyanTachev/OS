#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
int main(int agrc, char **argv)
{
	char error[100] = "./multifork ";
	int counter = atoi(argv[1]);
	char *filename = argv[2];
	pid_t pid;

	for(int i=0;i<counter;i++)
	{
		pid = fork();
		if(pid < 0) perror("fork");
		else if(pid == 0)
		{
			int res = execl(argv[2],argv[2],argv[3],0);
			if(res == -1)
			{
				strcat(error,argv[2]);
				perror(error);
				kill(pid,SIGKILL);
				
			}
		}
		else 
		{
			waitpid(pid,0,0);
		}
	}
	return 0;
}
