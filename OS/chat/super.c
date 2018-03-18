#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 100

int main(int argc, char*argv[]){

	int fd = open (argv[1],O_RDONLY);
	int fd1 = open (argv[2],O_WRONLY);

	char buffer[SIZE];
	ssize_t rbytes;

	int pid = fork();
	if (pid < 0) 
	{
		perror ("fork");
	}

	else if(pid == 0) 
	{   
		while ((rbytes = read(fd, buffer, SIZE)) != 0) 
		{
			write(STDOUT_FILENO, buffer, rbytes);
		}
		
	} 
	else  
	{  
		while ((rbytes = read(STDIN_FILENO, buffer, SIZE)) != 0) 
		{
			write(fd1, buffer, rbytes);
		}
	}

	close (fd);
	close (fd1);

	return 0;
}