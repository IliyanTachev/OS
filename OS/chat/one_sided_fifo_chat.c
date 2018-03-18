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

	int fd1 = open("chat1",O_RDWR); 

		//file1
		int pid_chat1 = fork();
		if (pid_chat1 < 0) perror("fork");
		else if (pid_chat1 == 0)
		{
			while((rbytes = read(fd1,buffer,SIZE)) != 0)
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

	return 0;
}