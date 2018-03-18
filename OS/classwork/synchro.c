#include <pthread.h>
#include <stdio.h>
#include <math.h>
#define NUM_OF_THREADS 2 
#define ARRAY_SIZE 10000

double total;
pthread_mutex_t mutex;

void* sum(void* attr)
{
	int i;

	for (i = 0; i < ARRAY_SIZE / NUM_OF_THREADS; ++i)
	{
		pthread_mutex_lock(&mutex);
		total += sin(i) * sin(i) + cos(i) * cos(i);
		pthread_mutex_unlock(&mutex);
	}

	return NULL;
}

int main()
{
	// pthread_mutex_t mutex;
	pthread_t threads[NUM_OF_THREADS];
	pthread_mutex_init(&mutex,NULL);
	
	int i;
	
	for (int i = 0; i < NUM_OF_THREADS; ++i)
	{
		pthread_create(&threads[i],NULL,sum,NULL);
	}

	for (int i = 0; i < NUM_OF_THREADS; ++i)
	{
		pthread_join(threads[i], NULL);
	}

	printf("Sum = %f\n",total);
	pthread_mutex_destroy(&mutex);
	return 0;
}