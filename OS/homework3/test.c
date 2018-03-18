#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<string.h>
#include<stdlib.h>
int main(int argc, char **argv)
{
	write(STDOUT_FILENO,"==> ",4);
	write(STDOUT_FILENO,"standard input",14);
	write(STDOUT_FILENO," <==\n",5);

	int i=0, size = 50, y=0, count=1;
	char *current = malloc(size*sizeof(char));
	char **array = malloc(count*sizeof(char*));
	for(i=0;scanf("%s",array[i])!= EOF;++i)
	{

		if(i>=count) 
		{
			array = realloc(array, (count+2)*sizeof(char*));
			count+=2;
		}
		for(y=0;scanf("%c",&current[y])!='\n';++y)
		{
			if(y>=size)
			{
				current = realloc(current, (size+2)*sizeof(char));
				size+=2;
			}
		}
	
	}
	printf("%s",array[0]);
	/*for(int g=0;g<strlen(*array);g++)
	{
		printf("\n%s",array[g]);
	}*/
	return 0;
}
