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
	
	int fd_write = open("chat2",O_WRONLY);
	int fd_read = open("chat1",O_RDONLY);

	while((rbytes = read(fd_read,buffer,SIZE)) != 0)
	{
			write(STDOUT_FILENO,buffer,rbytes);
	}

	while((rbytes = read(STDIN_FILENO,buffer,SIZE)) != 0)
	{
				write(fd_write,buffer,rbytes);
	}

	close(fd_read);
	close(fd_write);

	return 0;
}