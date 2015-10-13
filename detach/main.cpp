#include <pthread.h>
#include <stdio.h>
#include <unistd.h>


typedef struct 
{
	int num;
	volatile int *counter;
	volatile int *stop;
} ThreadInfo;

void* thread(void *param) 
{
	ThreadInfo *ti = (ThreadInfo*) param;

	ti->counter++;

	printf("Started %d\n",ti->num);

	while(!*(ti->stop)) 
	{
		printf("%d\n",ti->num);
	}

	printf("Finished %d\n",ti->num);

	ti->counter--;
	delete ti;
	pthread_exit(0);
}


int main(int c, char **v)
{

	volatile int counter = 0;
	volatile int stop = 0;

	for (int i=0;i<5;i++)
	{
		pthread_t th;

		ThreadInfo *ti = new ThreadInfo;
		ti->num = i;
    ti->counter = &counter;
		ti->stop = &stop;

		pthread_create(&th,NULL,thread,ti);
	}

  sleep(1);

	stop++;

	while(counter);

	return 0;
}
