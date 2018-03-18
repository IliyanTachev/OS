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
	char* chat1 = "chat1: ";
	char* chat2 = "chat2: ";
	char* typeIN_chat1 = "Type in CHAT1: ";
	char* typeIN_chat2 = "Type in CHAT2: ";

	int fd = open("chat",O_RDWR);
	while(1)
	{
		int pid_chat1 = fork();
		if (pid_chat1 < 0) perror("fork");
		else if (pid_chat1 == 0)
		{
			// write(STDOUT_FILENO,"child",5);
			while((rbytes = read(fd,buffer,SIZE)) != 0)
			{
				// write(STDOUT_FILENO,"child_while",10);
				write(STDOUT_FILENO,"\n",1);
				write(STDOUT_FILENO,chat1,strlen(chat1));
				write(STDOUT_FILENO,buffer,rbytes);
				break;
			}
		
		}
		else
		{
			//waitpid(pid,0,0);
			// write(STDOUT_FILENO,"parent",6);
			write(STDOUT_FILENO,typeIN_chat1,strlen(typeIN_chat1));
			while((rbytes = read(STDIN_FILENO,buffer,SIZE)) != 0)
			{
				// write(STDOUT_FILENO,"parent_while",11);
				write(fd,buffer,rbytes);
			}
		}
	
		int pid_chat2 = fork();
		if (pid_chat2 < 0) perror("fork");
		else if (pid_chat2 == 0)
		{
			// write(STDOUT_FILENO,"pit",3);
			while((rbytes = read(fd,buffer,SIZE)) != 0)
			{
				write(STDOUT_FILENO,"\n",1);
				write(STDOUT_FILENO,chat2,strlen(chat2));
				write(STDOUT_FILENO,buffer,rbytes);
				break;
			}
		}
		else
		{
			write(STDOUT_FILENO,typeIN_chat2,strlen(typeIN_chat2));
			while((rbytes = read(STDIN_FILENO,buffer,SIZE)) != 0)
			{
				write(fd,buffer,rbytes);
			}
		}
	}

	close(fd);

	return 0;
}