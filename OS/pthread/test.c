#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <conio.h>
#define NUM_THREADS 100

void *primes(void *number)
{
	int n = (int) number;
	printf("\nPrime calculation started for N=%d!",n);
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
        
        printf("\nNumber of primes for N=%d is %d",n,counter);
		pthread_exit(NULL);
}

int main()
{
	pthread_t threads[NUM_THREADS];
	int number = 0;
	int t = 0;
	while(1)
	{

		if(getch() == 'p')
		{
			scanf("%d",&number);
			int rc = pthread_create(&threads[t],NULL,primes,(void *)number);
		}
		else if(getch == 'e') break;
		else printf("gosho");
	}

	pthread_exit(NULL);
	
	return 0;
}