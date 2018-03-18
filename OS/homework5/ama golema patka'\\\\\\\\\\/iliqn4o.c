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
	char *buffer = NULL;
	while(1)
	{
   		write(1,"$ ",2);
		
   		size_t bufsize = 30;

	   	getline(&buffer,&bufsize,stdin);
	   	if(feof(stdin)){break;}
 
	   	char **result = parse_cmdline(buffer);
		for(int az = 0;result[az] != NULL;az++)write(1,result[az],strlen(result[az]));
		pid_t pid = fork();
		if(pid < 0) perror("fork");
		else if(pid == 0)
		{
			int res = execv(result[0],result);
			if(res == -1)
			{	
				free(buffer);
				perror(result[0]);
				exit(0);
				
			}
			exit(0);
		}
		else 
		{
			waitpid(pid,0,0);
		}

		free(result);	
		free(buffer);

		buffer = NULL;
	}

	free(buffer);
	return 0;
}
char **parse_cmdline(const char *cmdline)
{
	   char line[strlen(cmdline)];
           strcpy(line,cmdline);
	   int size = 1;
	   char **array = malloc(size*sizeof(char*));
	   char *token1 = NULL;
	   char *token2 = NULL;
   	   int i=0;
 	   token1 = strtok(line, "\n");
	   token2 = strtok(token1," ");
	   while(token2 != NULL ) 
	   {
		array[i] = token2;		
	      	token2 = strtok(NULL, " ");	
		i++;
		if(i >= size)
		{	
			size = size + 1; 
			array = realloc(array,size*sizeof(char*));
		}
	   }

	   //size+=1; 
	   //array = realloc(array,size*sizeof(char*));
	   //array[i] = token2;
	   //intf("\nsize of array: %ld",sizeof(array));
	   //for(int k=0;array[k]!=NULL;++k) printf("\n%d",k+1);
	  
	 return array;	
}
