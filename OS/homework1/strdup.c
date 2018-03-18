#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char *strdup (const char*);
int main()
{	
	char str[]={"abrakadabra"};
	char* result=strdup(str);
	return 0;
}
char *strdup (const char* input_array)
{
	//printf("%ld",strlen(input_array));
	char *arr=malloc((strlen(input_array)+1)*sizeof(char));
	int i=0;
	for(i=0;i<=strlen(arr);i++)
	{
		*(arr+i)=*(input_array+i);
	}	
 return arr;
}
