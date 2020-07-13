#include<stdio.h>
#include<unistd.h>
#include <stdlib.h>
#include<pthread.h>
#include<string.h>

#define LEFT 30000000
#define RIGHT 30000200
#define THRNUM  10

void debug(int i)
{
	printf("%d\n",i);
}


static int num = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *func(void *p);

int main()
{
	int i,err;
	pthread_t tid[THRNUM];


	for(i = 0 ; i < THRNUM ; i++ )
	{	
		
		err = pthread_create(tid+i,NULL,func,(void*)i);
		if(err)
		{
			fprintf(stderr,"err = %s",strerror(err));
			exit(1);
		}
	}
	for(i = LEFT ; i < RIGHT; i++ )
	{
		pthread_mutex_lock(&mutex);
		while(num != 0)
		{	
			pthread_mutex_unlock(&mutex);
			sched_yield();
			pthread_mutex_lock(&mutex);
		}
		num = i;
		pthread_mutex_unlock(&mutex);
	}
	pthread_mutex_lock(&mutex);
	while(num != 0)
	{
		pthread_mutex_unlock(&mutex);
		sched_yield();
		pthread_mutex_lock(&mutex);
	}
	num = -1;
	pthread_mutex_unlock(&mutex);
	for(i = 0; i < THRNUM ; i++ )
	{
		pthread_join(tid[i],NULL);
	}

	exit(0);

}

void* func(void *p)
{
	int j =0;
	int i =0;
	while(1)
	{
		pthread_mutex_lock(&mutex);
		while(num == 0)
		{
			pthread_mutex_unlock(&mutex);
			sched_yield();
			pthread_mutex_lock(&mutex);
		}
		
		if(num == -1)
		{
			pthread_mutex_unlock(&mutex);
			break;	
		}
		i = num;
		num = 0;
		pthread_mutex_unlock(&mutex);
		int adc = 1;
		for(j=2;j<(i/2);j++)
		{
			if(i%j==0)
			{
				adc = 0;
				break;
			}
		}
		if(adc)
			printf("[%d]%d is prime\n",(int)p , i);
	}
	pthread_exit(NULL);
}
