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
	   	char *buffer;
           	const char *res_buffer;
	  
   	   	size_t bufsize = 30;
		write(STDOUT_FILENO,"$",1);
	   	getline(&buffer,&bufsize,stdin);
	   	if(buffer[0] == EOF)break;
		res_buffer = buffer;

	   	char **result = parse_cmdline(res_buffer);
    	   
		
		 /*printf("\nelement [%d] -> %s",0,result[0]);
		 printf("\nelement [%d] -> %s",1,result[1]);
		 printf("\nelement [%d] -> %s",2,result[2]);
	        */
		pid_t pid;
	        
		pid = fork();
		if(pid < 0) perror("fork");
		else if(pid == 0)
		{
			int res = execv(result[0],result);
			if(res == -1)
			{
				//strcat(error,argv[2])
				perror(result[0]);
				
			}
		}
		else 
		{
			waitpid(pid,0,0);
		}
		exit(pid);

		free(result);
	}
	return 0;
}

char **parse_cmdline(const char *cmdline)
{
	   	int max_size_arrays = 1;
		
	 	char **array = (char**)malloc(max_size_arrays+1*sizeof(char*));

		int i=0,j=0,n=1;

	      	for(int t=0;cmdline[t]!='\0';t++,i++)
		{
			if(i >= max_size_arrays)
			{
				//printf("\n%s",array[i-1]);
				max_size_arrays += 5;
				array = (char **)realloc(array,max_size_arrays*sizeof(char*));
			
//				printf("\nBAI GOSHO! max_size_arrays = %d",max_size_arrays);
				
			}
//			printf("\nn = %d",n);
			array[i] = (char*)malloc(n*sizeof(char));

			while(cmdline[t]!=' ')
			{
				if(cmdline[t] == '\n')break;
				if(j >= n)
				{
					n+=5;
					array[i] = (char*)realloc(array[i],n*sizeof(char));
				}

				array[i][j] = cmdline[t];
				j++;				
				t++;
			}
			n=1;
			j=0;			
		}
			
	array = (char **)realloc(array, ++max_size_arrays);
	array[i] = NULL;

	return array; 
}
