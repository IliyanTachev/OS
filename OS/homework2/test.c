#include<stdio.h>
int main(int arc,char **argv)
{
	char *a;
	for(a=argv[1];*a!='\0';a++);
		if(*(a-1)=='g' && *(a-2)=='n' && *(a-3)=='p')printf("\ntrue");
		else printf("\nfalse");
	
	return 0;
}
