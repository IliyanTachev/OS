#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include<string.h>
#include<stdlib.h>

#define SIZE 100

int main(int argc, char const *argv[])
{
	char c;
	ssize_t rbytes;
	char buffer[SIZE];

	int fd1 = open("chat1",O_WRONLY); 
	int fd2 = open("chat2",O_RDONLY); //same as O_RDWR

		//file1
		int pid_chat1 = fork();
		if (pid_chat1 < 0) perror("fork");
		else if (pid_chat1 == 0)
		{
			while((rbytes = read(fd2,buffer,SIZE)) != 0)
			{
				write(STDOUT_FILENO,"\nUser said: ",12);
				write(STDOUT_FILENO,buffer,rbytes);
			}
			
		}
		else
		{
			while((rbytes = read(STDIN_FILENO,buffer,SIZE)) != 0)
			{
					write(fd1,buffer,rbytes);
			}
		}


	close(fd1);
	close(fd2);

	return 0;
}