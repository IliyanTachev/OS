#include<stdio.h>
#include<string.h>
char* strcat (char* destination, const char* source);
int main()
{	
	char destination[2000]={"hello"};
	char source[1000]={" pesho"};
 	char* array=strcat(destination,source);
	for(int i=0;i<strlen(array);i++)printf("%c",*(array+i));
	return 0;
}
char* strcat (char* destination, const char* source)
{
	int i=0,b=0,br=0;
	for(i=0;destination[i]!='\0';i++);
	for(b=i;source[br]!='\0';b++,br++)
	{
		destination[b]=source[br];
	}
	return destination;
}
