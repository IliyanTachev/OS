#include <stdio.h>
#include <unistd.h>	
#include <pthread.h>
#define NUM_OF_THREADS 2 

int gold = 0;
pthread_mutex_t mutex;

void pthreadjoin(pthread_t[], int);

void *dig(void* attr) {
   
   
    for(int k = 0; k < 20; k++) {
   
        pthread_mutex_lock(&mutex);
        printf("Miner %d gathered 10 gold\n",(int)attr);
        gold += 10;
        pthread_mutex_unlock(&mutex);
 
        sleep (2); 
    }
   
    return NULL;
}
 
void *sell(void* attr) 
{
   
    for(int k = 0; k < 20; k++) 
    {
 
        pthread_mutex_lock(&mutex);
 
        if (gold == 0) 
        {
            printf("The warehouse is empty,cannot sell!\n");
        } 
        else 
        {
            printf("Trader %d sold 10 gold\n",(int)attr);
            gold -= 10;
        }  
        pthread_mutex_unlock(&mutex);
        sleep (2);
       
    }
   
    return NULL;
}

int main(int argc, char** argv) 
{
	int miners_count = 1;
	int traders_count = 1;

	if(argc > 1) 
	{
		miners_count = atoi(argv[1]);
		traders_count = atoi(argv[2]);
	}

	pthread_t miners[miners_count];
	pthread_t traders[traders_count];
	
	pthread_mutex_init(&mutex,NULL);

	for (int i = 0; i < miners_count; ++i)
	{
			pthread_create(&miners[i],NULL,dig,(void*)i+1);
	}
	
	for (int i = 0; i < traders_count; ++i)
	{
			pthread_create(&traders[i],NULL,sell,(void*)i+1);
	}

	pthreadjoin(miners,miners_count);
	pthreadjoin(traders,traders_count);


	printf("Gold: %d\n",gold);
	pthread_mutex_destroy(&mutex);
	// pthread_exit(NULL);       

	return 0;
}

void pthreadjoin(pthread_t array[], int count) 
{
	for(int i=0;i<count;i++)
	{
		int rc = pthread_join(array[i],NULL);
		if(rc)
		{
			printf("ERROR: pthread_join() return %d\n",rc);
			exit(-1);
		}
	}
}
