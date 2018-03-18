#include<stdio.h>
int main()
{
	int n = 0;
	printf("\nInput a number: ");
	scanf("%d",&n);

		int counter = 0;

		int checkprime(int n) 
	      	{
            	if (n == 1) return 0;
            	else
            	{
                	for (int i = 2; i <= n / 2; i++) 
                	{
                    	if (n % i == 0) 
                    	{
                        	return 0;
                    	}
                    }
                }

                return 1;
            }
		
        for (int i = 2; i < n; i++)
        {
            int res = checkprime(i);
            if (res == 1) counter++;
        }
            
            printf("Answer: %d",counter);
        

	return 0;
}
