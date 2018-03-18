#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char **parse_cmdline(const char *cmdline);

int main()
{
        
	char *buffer;
   	size_t bufsize = 30;
    	size_t characters;

    	buffer = (char *)malloc(bufsize * sizeof(char));
        characters = getline(&buffer,&bufsize,stdin);
	char **result = parse_cmdline(buffer);
	return 0;
}
char **parse_cmdline(const char *cmdline)
{
  
	char **array = malloc(10*sizeof(char*));
    		
    	printf("You typed: '%s'\n",cmdline);	

	char *token1;
	char *token2;
   	int i=0;

 	token1 = strtok(cmdline, "\n");
	token2 = strtok(token1," ");
   
	while(token2 != NULL ) 
	{
		printf( "%s\n", token2 );

		array[i] = malloc(1*sizeof(token2));

		for(int y=0;y<strlen(token2);++y)
		array[i][y] = token2[y];
		
	      	token2 = strtok(NULL, " ");
		i++;
	}
	
	return array;
}
