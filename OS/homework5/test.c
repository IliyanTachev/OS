#include<stdio.h>
#include<string.h>

int main()
{
	int array[]={1,2,3,4,5,6,7,8,9,10};
	for(int j=1;j<sizeof(array)/4;j++)
	{
		array[j-1] = array[j];
	}
	
	for(int i=0;i<sizeof(array)/4;i++)printf("\n%d",array[i]);
	
	return 0;
}
