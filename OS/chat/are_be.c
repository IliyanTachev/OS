#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include<string.h>
#include<stdlib.h>

#define SIZE 20

int main(int argc, char const *argv[])
{
	char c;
	ssize_t rbytes;
	char buffer[SIZE];

	int fd1 = open("chat1",O_WRONLY);
	int fd2 = open("chat2",O_RDONLY);

		//file1
		int pid_chat1 = fork();
		if (pid_chat1 < 0) perror("fork");
		else if (pid_chat1 == 0)
		{
			 // write(STDOUT_FILENO,"file1 ",6);
			while((rbytes = read(fd2,buffer,SIZE)) != 0)
			{
				write(STDOUT_FILENO,buffer,rbytes);
			}
			
		}
		else
		{
			// waitpid(pid_chat1,0,0);
			 //write(STDOUT_FILENO,"file1 typed ",12);
			while((rbytes = read(STDIN_FILENO,buffer,SIZE)) != 0)
			{
					write(fd1,buffer,rbytes);
			}
		}


	close(fd1);
	close(fd2);

	int fd3 = open("chat1",O_RDONLY);
	int fd4 = open("chat2",O_WRONLY);

		//file2
		int pid_chat2 = fork();
		if (pid_chat2 < 0) perror("fork");
		else if (pid_chat2 == 0)
		{
			 // write(STDOUT_FILENO,"file2 ",6);
			while((rbytes = read(fd3,buffer,SIZE)) != 0)
			{
				write(STDOUT_FILENO,buffer,rbytes);			
			}
		}
		else
		{
			//write(STDOUT_FILENO,"file2 typed ",12);
			 // waitpid(pid_chat2,0,0);
			while((rbytes = read(STDIN_FILENO,buffer,SIZE)) != 0)
			{
					write(fd4,buffer,rbytes);
			}
		
		}


	close(fd1);
	close(fd2);

	return 0;
}