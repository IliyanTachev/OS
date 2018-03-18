#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 20

int main(int argc, char const *argv[])
{
	ssize_t rbytes;
	char buffer[SIZE];
// while(1)
// {
	int pid = fork();
	if(pid < 0) perror("fork");
	else if(pid == 0)
	{
		int fd = open("chat1",O_WRONLY);

		write(STDOUT_FILENO,"chat1: ",7);
		while((rbytes = read(STDIN_FILENO,buffer,SIZE)) != 0)
		{
			write(STDOUT_FILENO,"chat1: ",7);
				write(fd,buffer,rbytes);
				// break;
		}
		
		close(fd);
	}
	else
	{
		waitpid(pid,0,0);
		int fd2 = open("chat2",O_WRONLY);

		write(STDOUT_FILENO,"chat2: ",7);

		while((rbytes = read(STDIN_FILENO,buffer,SIZE)) != 0)
		{
			write(STDOUT_FILENO,"chat2: ",7);
				write(fd2,buffer,rbytes);
		}

		close(fd2);
	}
// }
	return 0;
}
