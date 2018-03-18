#include<stdio.h>
void swap(int*, int*);
int main()
{
	int  a=5,b=4;
	printf("\na=5, b=4\n");
	swap(&a,&b);
	printf("A changed to %d\n",a);
	printf("B changed to %d\n",b);
	return 0;
}
void swap(int *a, int *b)
{
	int c=0;
 	c=*a;
	*a=*b;
	*b=c;
}
