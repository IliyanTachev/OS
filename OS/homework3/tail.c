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
#include <stdlib.h>
void standardInput(void);
int print_headers(char **,int,int);
int main(int argc, char **argv)
{
	int count = 1; 
	if(argc == 1) standardInput();
	for(int t=1;t<argc;t++)					//преминаване през всеки аргумент от командния ред
	{

		char ch;
		int br=0;
		if(argv[t][0] == '-')
		{
			if(argc > 2) count = print_headers(argv,t,count);
			standardInput();
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
			
		for(k=position;k<size;)			
		{
				
				ssize_t readed = read(fd,&ch,1);
				ssize_t written = write(STDOUT_FILENO,&ch,1);
				if(readed == 0) continue;
				if(written < 0)
				{

					char *first_half = "tail: error writing 'standard output'";
		                        
					perror(first_half);
					
					break;
				}
				else if(written == 0)
				{	
					lseek(fd,-1,SEEK_CUR);
					continue;
				}
				k++;
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
//------------------------------------------------------------------------
// FUNCTION: standardInput 
// изпълнение на STDIN функционалност
// PARAMETERS:
// няма
// 
//------------------------------------------------------------------------
void standardInput(void)
{	
	int size = 10; 
	int new_lines_counter = 0,i=0; 
	char *array =  malloc (size * sizeof(char)); //заделяме памет
	for (i = 0;scanf("%c",&array[i]) != EOF;i++) 
	{
		if(i >= size)
		{
			size += 2;
			array = realloc (array,size); //реалокираме ако има нужда
		}
	}
	int count_back = strlen(array) - 1; 		
	char arr[size]; 		
	int br = 0; 			
	for(;count_back > -1; count_back--)  // сканираме отзад напред масива и четем до 0лев елемент
	{
		if(array[count_back] == '\n') 
		{
			new_lines_counter ++;
			if (new_lines_counter == 11) break; 
		}
		arr[br++] = array[count_back];	
	}

	for (br--; br > -1 ;br -- )
	{
		write(STDOUT_FILENO,&arr[br],1);
	}
	free(array);

}
//------------------------------------------------------------------------
// FUNCTION: print_headers (име на функцията)
// принти хедърите
// PARAMETERS:
// char **argv,int curr_element,int count
// взима съответния аргумент от командния ред, взима индекса му, колко пъти се е викнала функцията
//------------------------------------------------------------------------
int print_headers(char **argv,int curr_element,int count)
{
   		 if (count > 1) write(STDOUT_FILENO, "\n",1);

  		 write(STDOUT_FILENO, "==> ",4);

  		 if (argv[curr_element][0] == '-') write(STDOUT_FILENO,"standard input",14);
 		 else write(STDOUT_FILENO, argv[curr_element],strlen(argv[curr_element]));
 	
		 write(STDOUT_FILENO, " <==\n",5);
	
 		 return count += 1;      
}

