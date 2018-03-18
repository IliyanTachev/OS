#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main()
{
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
			printf("%c",array[e]);
		}
	}
	else 
	{
		for(int e=r;e<strlen(array);e++)
		{
			printf("%c",array[e]);
		}
	}
	free(array);

	return 0;
}
