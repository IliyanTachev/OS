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
           const char *buffer;
	  
   	   size_t bufsize = 30;

	   getline(&buffer,&bufsize,stdin);
    	   //size_t characters;

    	   //buffer = (char *)malloc(bufsize * sizeof(char));
  	   int max_size_arrays = 10;
		
	   char **array = (char**)malloc(max_size_arrays*sizeof(char*));

	   for(int br =0 ; br < max_size_arrays ; br++)
		array[br] = (char*)malloc(100*sizeof(char));
	   
		int i=0,j=0,n=10;

	  char buff;
    	  for(;buff != '\n';)
	  {
		if(buff == ' ')
		{
			i++;
			if(i == max_size_arrays)
			{
				array = (char**)realloc(*array, sizeof(char*) * (max_size_arrays + 2));
				max_size_arrays+=2;
			}

			j=0;
			
			read(STDIN_FILENO,&buff,1);
			write(STDOUT_FILENO,&buff,1);
			array[i][j++] = buff;

			if(j == n)
			{
				array[i] = (char*)realloc(array[i],n+2);
				n+=2;	
			}
				
		}

		read(STDIN_FILENO,&buff,1);
		write(STDOUT_FILENO,&buff,1);
		array[i][j++] = buff;

		if(j == n)
		{
			array[i] = (char*)realloc(array[i],n+2);
			n+=2;				
		}  
	  } 
		//for(int e = 0; e <= i;e++)
		//printf("\nHALOO: %s",array[e]);
   		//printf("i = %d",i);
	   //while(token2 != NULL ) 
	   //{
 	     	//printf( "%s\n", token2 );

		//array[i] = malloc(1*sizeof(token2));

	//	for(int y=0;y<strlen(token2);++y)
	//	array[i][y] = token2[y];
		
	     // 	token2 = strtok(NULL, " ");
	//	i++;
	  // }

// ===========================================================================================================================

	   //char error[100] = "./multifork ";
	   //char *filename = array[0];
	   /*char **changed_array = (char**)malloc((i-1) * sizeof(char*));
	   for(int d=0,p=1;d<=i-1;d++,p++)
	   {
		changed_array[d] = array[p];
	   }	
	   /*for(int d = 0; d <= i-1; d++)
	   {
		printf("\nZeleno: %s",changed_array[d]);
	   }*/
	
	  pid_t pid;
	
		pid = fork();
		if(pid < 0) perror("fork");
		else if(pid == 0)
		{
			int res = execv(array[0],array);
			if(res == -1)
			{
				//strcat(error,argv[2])
				perror("error");
				kill(pid,SIGKILL);
				
			}
		}
		else 
		{
			waitpid(pid,0,0);
		}
	
	free(array);
 	 
	return 0;
}
char **parse_cmdline(const char *cmdline)
{
	
}
