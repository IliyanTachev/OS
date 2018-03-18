#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>


char **parse_cmdline(const char *cmdline);
void fork_pipe(char **array1, char **array2);

int size_array = 0;

int main()
{
	
	while(1)
	{
   		write(STDOUT_FILENO,"$ ",2);
		char *buffer = NULL;
   		size_t bufsize = 30;
		int check_pipe = 0;

	   	getline(&buffer,&bufsize,stdin);
	   	if(feof(stdin))
		{
			free(buffer);
			break;
		}
 
	   	char **result  = parse_cmdline(buffer);
		free(buffer);
// ===========================================================================================================================
		/*for(int i = 0; result[i] != NULL; i++)
		{
			  write(STDOUT_FILENO,"\n",1);
			  write(STDOUT_FILENO,"pochvame 1",10);
        	          write(STDOUT_FILENO,result[i],strlen(result[i]));
       		}*/
		
		for(int i=0;i<size_array;++i)
		{
			if(result[i] == "|")
			{
				check_pipe = 1;
				printf("koo");
				
			}
//			printf("koo");
		}		
		
		if(check_pipe == 1)
		{
			char **array1,**array2;
			int k=0;

			for(k=0;result[k]!="|";++k) array1[k] = result[k];	
			for(int i=k+1;i<size_array;++i) array2[i] = result[i];
			
			fork_pipe(array1,array2);
		}
		else 
		{
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
	   {	
		array[i] = malloc ((strlen(token2)+1) * sizeof(char));
		strcpy(array[i],token2);		
	      	token2 = strtok(NULL, " ");
		i++;
		size_array++;

		if(i == size)
		{
			size =size+1;
			array = realloc(array,size*sizeof(char*));
		}
	   }
	   array[i] = NULL;
	   free(line);

	return array;	


}

void fork_pipe(char **array1, char **array2)
{
	pid_t pid;
   	int fd[2];

    	pipe(fd);
    	pid = fork();

    	if(pid==0)
    	{	
        	
       	 	dup2(fd[1], STDOUT_FILENO);
       	 	close(fd[1]);
        	//execlp("ls", "ls", "-al", NULL);
		execv(array1[0],array1);
    	}
    	else
    	{ 
       	 	pid=fork();

        	if(pid==0)
        	{
            		
            		dup2(fd[0], STDIN_FILENO);
            		close(fd[0]);
            		//execlp("grep", "grep", "alpha",NULL);
			execv(array2[0],array2);
        	}
    	}
}
