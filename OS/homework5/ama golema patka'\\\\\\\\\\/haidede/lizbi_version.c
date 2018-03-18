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
	
	while(1)
	{
   		write(STDOUT_FILENO,"$ ",2);
		char *buffer = NULL;
   		size_t bufsize = 30;

	   	getline(&buffer,&bufsize,stdin);
	   	if(feof(stdin))
		{
			free(buffer);
			break;
		}
 
	   	char **result  = parse_cmdline(buffer);
		free(buffer);
// ===========================================================================================================================
		pid_t pid = fork();
		if(pid < 0) 
		{
			perror("fork");
			for(int i = 0; result[i] != NULL; i++)
			{
                    		free(result[i]);
                	}

                	free(result);
		}
		else if(pid == 0)
		{
			int res = execv(result[0],result);
			if(res == -1)
			{	
				perror(result[0]);
				for(int i = 0; result[i] != NULL; i++)
				{
                    			free(result[i]);
                		}

                		free(result);
				exit(0);
				
			}
		
		}
		else 
		{
			waitpid(pid,0,0);
			for(int i = 0; result[i] != NULL; i++)
			{
                	    	free(result[i]);
               		}

                	free(result);
		}

		
	}
	return 0;
}

char **parse_cmdline(const char *cmdline)
{	
	   char *line = malloc (strlen(cmdline) + 1);

	   strcpy(line,cmdline);
	   int size = 2;
	   char **array = malloc(size*sizeof(char*));
	   char *token1;
	   char *token2;
   	   int i=0;
 	   token1 = strtok(line, "\n");
	   token2 = strtok(token1," ");
	   while(token2 != NULL ) 
	   {	array[i] = malloc (strlen(token2)*sizeof(char*));
		strcpy(array[i],token2);		
	      	token2 = strtok(NULL, " ");
		i++;
		if(i == size){
		size =size+1;
		array = realloc(array,size*sizeof(char*));
		}
	   }
	   array[i] = NULL;
	   free(line);

	return array;	
}
