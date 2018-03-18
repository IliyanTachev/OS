#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

int warehouse = 0;
pthread__mutex_t mutex;

void *miner_func(void *arg)
{
	for (int i = 0; i < 20; ++i)
	{
		pthread_mutex_lock(&warehouse_mutex);
		warehouse+=10;
		pthread_mutex_unlock(&warehouse_mutex);
		printf("Miner %d mined 10 gold\n",);
		sleep(2);
	}

	return NULL;
}
void *trader_func(void *arg)
{
	for (int i = 0; i < 20; ++i)
	{
		pthread_mutex_lock(&warehouse_mutex);
		
		if(warehouse <= 0) printf("Warehouse is empty for trader 1\n");
		else {
				warehouse-=10;
				printf("Trader 1 sold 10 gold\n");
		}

		pthread_mutex_unlock(&warehouse_mutex);

		sleep(2);
	}

	return NULL;
}

int main(int argc, char **argv)
{
	int miner_count = 1;
	int trader_count = 1;
	pthread_t miner[100];
	pthread_t trader[100];
	
	if(argc > 1)
	{
		miner_count = atoi(argv[1]);
		trader_count = atoi(argv[2]);
	}

	if(pthread__mutex_init(&warehouse_mutex, NULL) != 0)
	{
		perror("pthread_");
		return 4;
	}

	for (int i = 0; i < miner_count; ++i)
	{
		if(pthread_create(&miner, NULL, miner_func, (void *)i) != 0)
		{
			perror("pthread_join");
			return 5;
		}
	}

	for (int i = 0; i < trader_count; ++i)
	{
		if(pthread_create(&trader, NULL, trader_func, (void *)i) != 0)
		{
			perror("pthread_join");
			return 1;
		}
	}

	if(pthread_join(miner, NULL) != 0)
	{
		perror("pthread_join");
		return 2;
	}

	if(pthread_join(trader, NULL) != 0)
	{
		perror("pthread_join");
		return 3;
	}


	return 0;
}