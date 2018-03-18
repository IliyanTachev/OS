#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#define SIZE 20

int main(int argc, char const *argv[])
{
	char c;
	ssize_t rbytes;
	char buffer[SIZE];
	char* chat1 = "chat1: ";
	char* chat2 = "chat2: ";

	int fd = open("chat",O_RDWR);

	// while((rbytes = read(STDIN_FILENO,buffer,SIZE)) != 0)
	// {
	// 	write(fd,buffer,rbytes);
	// }
		 while(1)
		 {
		 	int counter = 0;
			int pid = fork();

			if (pid < 0) perror("fork");
			else if (pid == 0)
			{
					//write(STDOUT_FILENO,"kapan",5);
					while((rbytes = read(STDIN_FILENO,buffer,SIZE)) != 0)
					{
						write(fd,buffer,rbytes);
						//counter++;
					}
			}
			else
			{
					
					while((rbytes = read(fd,buffer,SIZE)) != 0)
					{
				 		//if(counter%2 == 0)write(STDOUT_FILENO,chat2,strlen(chat2));
				 		//else write(STDOUT_FILENO,chat1,strlen(chat1));
				 
						write(STDOUT_FILENO,buffer,rbytes);
					}

			}
		 }

	close(fd);

	return 0;
}
