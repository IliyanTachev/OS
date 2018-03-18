#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

char **parse_cmdline(const char *cmdline);
void free_memory(char **arr, size_t size);

int main()
{	
	//ILIQN E GOLQM GEI
		char *buffer = NULL;   	
		size_t bufsize = 30;
		write(STDOUT_FILENO,"$ ",2);
		while(1)
		{
			getline(&buffer,&bufsize,stdin);
			if(feof(stdin)){break;}
		   	char **result = parse_cmdline(buffer);    	   
		
			 /*printf("\nelement [%d] -> %s",0,result[0]);
			 printf("\nelement [%d] -> %s",1,result[1]);
			 printf("\nelement [%d] -> %s",2,result[2]);
		        */
	        	
			pid_t pid = fork();
			if(pid < 0) perror("fork");
			else if(pid == 0)
			{
				int res = execv(result[0],result);
				if(res == -1)
				{			
					perror(result[0]);
					exit(0);	
				}
				//exit(0);
				exit(0);
			}
			else 
			{
				waitpid(pid,0,0);
			}
		
			//exit(pid);
	
			size_t size = 0;	
			//write(STDOUT_FILENO,"iv",2);
				
			//free_memory(result,size);
			write(STDOUT_FILENO,"$ ",2);
		}
		exit(0);
		return 0;
}
	
char **parse_cmdline(const char *cmdline)
{
	   	int max_size_arrays = 1;
			
	 	char **array = (char**)malloc((max_size_arrays+1)*sizeof(char*));

		int i=0,j=0,n=1;

	      	for(int t=0;cmdline[t]!='\0';t++,i++)
		{
			if(i >= max_size_arrays)
			{
		
				max_size_arrays += 5;
				array = (char **)realloc(array,max_size_arrays);	
			}

			array[i] = (char*)malloc(n*sizeof(char));

			while(cmdline[t]!=' ')
			{
				if(cmdline[t] == '\n')break;
				if(j >= n)
				{
					n+=5;
					array[i] = (char*)realloc(array[i],n);
				}

				array[i][j] = cmdline[t];
				j++;				
				t++;
			}
			n=1;
			j=0;			
		}
	max_size_arrays++;
	array = (char **)realloc(array, max_size_arrays);
	array[++i] = NULL;

	for(int toshko=0;toshko<i;toshko++)
	{
		write(STDOUT_FILENO,"\n",1);
		write(STDOUT_FILENO,array[toshko],strlen(array[toshko]));
	}
	return array; 
}
void free_memory(char **arr, size_t size)
{
	for(int i=0;i<size;i++) free(arr[i]);
	free(arr);	
}

