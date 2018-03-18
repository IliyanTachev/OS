#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 100

int main(int argc, char const *argv[])
{
	ssize_t rbytes;
	char buffer[SIZE];

	int fd1 = open(argv[1],O_RDWR);
	int fd2 = open(argv[2],O_RDWR);

	int both = fork();
	if(both < 0) perror("fork");
	else if(both == 0)
	{
		// write(STDOUT_FILENO,"file1...",8);
		int pid_chat1 = fork();
		if (pid_chat1 < 0) perror("fork");
		else if (pid_chat1 == 0)
		{
			while((rbytes = read(fd2,buffer,SIZE)) != 0)
			{
				 write(STDOUT_FILENO,"1-read ",7);
				// write(STDOUT_FILENO,"\nUser said: ",12);
				write(STDOUT_FILENO,buffer,rbytes);
			
			}
			
		}
		else
		{
			while((rbytes = read(STDIN_FILENO,buffer,SIZE)) != 0)
			{
					write(STDOUT_FILENO,"1-write ",7);
					write(fd1,buffer,rbytes);
			}
		}
	}
	else
	{
		waitpid(both,0,0);
		
		int pid_chat2 = fork();
		if (pid_chat2 < 0) perror("fork");
		else if (pid_chat2 == 0)
		{
			while((rbytes = read(fd1,buffer,SIZE)) != 0)
			{
				  write(STDOUT_FILENO,"2-read ",7);
				// write(STDOUT_FILENO,"\nUser said: ",12);
				write(STDOUT_FILENO,buffer,rbytes);			
			}
		}
		else
		{
			// write(STDOUT_FILENO,"2-write ",7);
			while((rbytes = read(STDIN_FILENO,buffer,SIZE)) != 0)
			{
					write(STDOUT_FILENO,"2-write ",7);
					write(fd2,buffer,rbytes);
			}
		
		}
	}

	close(fd1);
	close(fd2);

	return 0;
}