#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

void parse_cmdline(const char *cmdline);

int main()
{
		char *buffer = NULL;
	
   		write(1,"$ ",2);
		
   		size_t bufsize = 30;

	   	getline(&buffer,&bufsize,stdin);
	        parse_cmdline(buffer);
			

	free(buffer);
	return 0;
}
void parse_cmdline(const char *cmdline)
{
	   char line[strlen(cmdline)];
           strcpy(line,cmdline);
	   int size = 2;
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
			size = size + 2; 
			array = realloc(array,size*sizeof(char*));
		}
	   }
	   array[i] = NULL;

	  for(int i=0;array[i]!=NULL;++i) write(STDOUT_FILENO,array[i],strlen(array[i]));
	  
	  free(array);	
}
