#include <stdio.h>

int main()
{
	int n = 0;
	int p = 0;
	int save_value = 0;
	scanf("%d",&n);
	scanf("%d",&p);

	save_value = n;
	if(p == 0) return 1;
	for(int i=0;i<p - 1;i++)
	{

		n=n*save_value;
	}

	printf("Result is: %d ",n);
	return 0;
}