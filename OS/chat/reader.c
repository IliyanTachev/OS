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

	int fd = open("chat",O_RDWR);
	// while(1)
	// {
		int pid = fork();

		if(pid < 0) perror("fork");
		else if(pid == 0)
		{
			write(STDOUT_FILENO,"child",5);
			while((rbytes = read(fd,buffer,SIZE)) != 0)
			{
				write(STDOUT_FILENO,buffer,rbytes);
			}
		}
		else 
		{
			write(STDOUT_FILENO,"vliza",5);
			while((rbytes = read(STDIN_FILENO,buffer,SIZE)) != 0)
			{
				write(fd,buffer,rbytes);
			}
		}
	// }

	close(fd);

	return 0;
}
