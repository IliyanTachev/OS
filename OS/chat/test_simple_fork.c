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
	int fd[2];
	pipe(fd);
	
	int fd = open("chat",O_RDWR);

	int pid = fork();

	if(pid < 0) perror("fork");
	else if(pid == 0)
	{
		
	}
	else 
	{
		
	}

	close(fd);

	return 0;
}