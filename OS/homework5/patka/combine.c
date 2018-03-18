#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

char **parse_cmdline(const char *cmdline);

int main()
{
	
	while( 1)
	{
   	write(STDOUT_FILENO,"$ ",2);
	char *buffer = NULL;
   	size_t bufsize = 30;

	   getline(&buffer,&bufsize,stdin);
	   if(feof(stdin)){break;}

    	   //characters = getline(&buffer,&bufsize,stdin);
	   //if(characters <= 0) exit(0); 
	   char **result  = parse_cmdline(buffer);
	
// ===========================================================================================================================
		pid_t pid = fork();
		if(pid < 0) perror("fork");
		else if(pid == 0)
		{
			int res = execv(result[0],result);
			if(res == -1)
			{	
				//strcat(error,argv[2]);
				perror("error");
				//kill(pid,SIGKILL);
				exit(0);
				
			}
			exit(0);
		}
		else 
		{
			waitpid(pid,0,0);
		}

	//free(result);
	
	}
	return 0;
}
char **parse_cmdline(const char *cmdline)
{
	   char *line;
		strcpy(line,cmdline);
		int size = 2;
	   char **array = malloc(size*sizeof(char*));
	   char *token1;
	   char *token2;
   	   int i=0;
 	   token1 = strtok(line, "\n");
	   token2 = strtok(token1," ");
	   while(token2 != NULL ) 
	   {
		array[i] = token2;		
	      	token2 = strtok(NULL, " ");
		i++;
		if(i == size){
		size =size+1;
		array = realloc(array,size*sizeof(char*));
		}
	   }
	array[i] = NULL;
	return array;	
}
