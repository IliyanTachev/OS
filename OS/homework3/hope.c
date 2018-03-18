//------------------------------------------------------------------------
// NAME: Iliyan Tachev
// CLASS: XIb
// NUMBER: 11
// PROBLEM: #1
// FILE NAME: tail.c
// FILE PURPOSE:
// реализиране на системната функция tail:
// програмата приема файлове като аргументи от командния ред и извежда последните 10 реда от тях
// ако даден файл съдържа по-малко от 10 реда се извежда цялото съдържание на файла 
//------------------------------------------------------------------------
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include<stdlib.h>
void standardInput(int);
int print_headers(char **,int,int);
int main(int argc, char **argv)
{
	int count = 1; 
	if(argc == 1) standardInput(argc);
	for(int t=1;t<argc;t++)					//преминаване през всеки аргумент от командния ред
	{

		char ch;
		int br=0;
		if(argv[t][0] == '-')
		{
			if(argc > 2) count = print_headers(argv,t,count);
			standardInput(argc);
			continue;
		}
		int fd = open(argv[t],0,O_RDONLY);			//отваряне на файла с индекс i
		char *filename = argv[t];
		if(fd < 0)
		{
                        
				char *first_half = "tail: cannot open '";
        	                char arr[strlen(first_half) + strlen(filename) + 1];
				char *second_half = "' for reading";

        	                int r=0,g=0,j=0,w=0;

        	                for(r=0,g=0;r<strlen(first_half) + strlen(filename);r++)
        	                {
        	                        if(r<strlen(first_half))arr[r] = first_half[r];
        	                        else
        	                        {
        	                                arr[r] = filename[g];
        	                                g++;
        	                        }
        	                }
			
				for(j=r,w=0;w<strlen(second_half);j++,w++)
				{
        	                	arr[j] = second_half[w];
				}	

				arr[j] = '\0';

				perror(arr);
			
			continue;
		}

		ssize_t catch_read_error = read(fd,&ch,1); 
		
		if(catch_read_error < 0) 
		{

				char *first_half = "tail: error reading '";
	                        char arr[strlen(first_half) + strlen(filename) + 1];
	                        int r=0,g=0,j=0,w=0;

	                        for(r=0,g=0;r<strlen(first_half) + strlen(filename);r++)
	                        {
	                                if(r<strlen(first_half)) arr[r] = first_half[r];
  	                                else
      	 	                        {
      	                                	arr[r] = filename[g];
       		                       	 	g++;
       		                        }
          		        }

				arr[r] = (char) 39;
				arr[r+1] = '\0';

				perror(arr);

			continue;
		}
		
 		if(argc > 2) 
		{
                	count = print_headers(argv,t,count);
        	}

		int i,k,check=0;
		off_t size = lseek(fd,0,SEEK_END);			//намиране на пълния размер на файла (брой байтове)
		off_t position;
		ssize_t read_bytes,write_bytes,readed;	
		
		for(i=-1;br<=10;i--)					//цикъл, въртящ се докато не се изброат 10 нови реда
		{
			position = lseek(fd,i,SEEK_END);		//+1 additional row up		
			if(position == 0)break;
			readed = read(fd,&ch,1);			//четене байт по байт	
			if(ch == '\n')br++;				//бройм новите редове
		}
		if(br>10)position = lseek(fd,0,SEEK_CUR);
			
		for(k=position;k<size;k++)			
		{
				
				ssize_t readed = read(fd,&ch,1);
				ssize_t written = write(STDOUT_FILENO,&ch,1);
				
				if(written < 0)
				{

					char *first_half = "tail: error writing 'standard output'";
		                        
					perror(first_half);
					
					break;
				}
		}
		
		int isClosedProperly = close(fd);
		if(isClosedProperly < 0) 						//затваряме файла
		{

				char *first_half = "tail: error reading '";
	                        char arr[strlen(first_half) + strlen(filename) + 1];
	                        int r=0,g=0,j=0,w=0;

	                        for(r=0,g=0;r<strlen(first_half) + strlen(filename);r++)
	                        {
	                                if(r<strlen(first_half)) arr[r] = first_half[r];
  	                                else
      	 	                        {
      	                                	arr[r] = filename[g];
       		                       	 	g++;
       		                        }
          		        }

				arr[r] = (char) 39;
				arr[r+1] = '\0';

				perror(arr);

		}
	}
	return 0;
}
void standardInput(int argc)
{
	/*if(argc>1)
	{	
		write(STDOUT_FILENO,"\n",1);
		write(STDOUT_FILENO,"==> ",4);
		write(STDOUT_FILENO,"standard input",14);
		write(STDOUT_FILENO," <==\n",5);
	}
	else
	{
		write(STDOUT_FILENO,"==> ",4);
		write(STDOUT_FILENO,"standard input",14);
		write(STDOUT_FILENO," <==\n",5);
	} */
	int size = 10;
	char *array = malloc(size*sizeof(char));
	int br=0,max=0,max_length=0;
	for(int i=0;scanf("%c", &array[i]) != EOF;i++)
	{
		
		if(i>=10)
		{
			array = realloc(array,size+2);
			size+=2;
		}
	}

	int r=0;
	int check=0;
	for(r = strlen(array);br<11;r--)
	{
		if(r==0) break;
		if(array[r]=='\n')
		{
			br++;
		}
		
	}
	if(br==11)check=1;
	if(check==1)
	{
		for(int e=r+1;e<strlen(array);e++)
		{
			write(STDOUT_FILENO,&array[e],1);
		}
	}
	else 
	{
		for(int e=r;e<strlen(array);e++)
		{
			write(STDOUT_FILENO,&array[e],1);
		}
	}
	free(array);
}
int print_headers(char **argv,int curr_element,int count)
{
   		 if (count > 1) write(STDOUT_FILENO, "\n",1);

  		 write(STDOUT_FILENO, "==> ",4);

  		 if (argv[curr_element][0] == '-') write(STDOUT_FILENO,"standard input",14);
 		 else write(STDOUT_FILENO, argv[curr_element],strlen(argv[curr_element]));
 	
		 write(STDOUT_FILENO, " <==\n",5);
	
 		 return count += 1;      
}

