#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<string.h>
pthread_mutex_t mutex[4];

int next(int n)
{
	n++;
	if(n==4)
		n = 0;
	return n ;
}

void* func(void *p)
{
	int n = (int)p;
	int c = 'a'+n;
	
	while(1)
	{
	
		pthread_mutex_lock(&mutex[n]);
		write(1,&c,1);
		pthread_mutex_unlock(mutex+next(n));
	}
	pthread_exit(NULL);
}

int main()
{
	int i = 0,ret=0;
	pthread_t pit[4];
	for(i = 0;i < 4;i++)
	{
		pthread_mutex_init(mutex+i,NULL);
		pthread_mutex_lock(mutex+i);
		ret = pthread_create(pit+i,NULL,func,(void*)i);
		if(ret)
		{
			fprintf(stderr,"pthread_create(): %s",strerror(ret));
			exit(1);
		}
	}
	pthread_mutex_unlock(&mutex[0]);
	for(i=0;i<4;i++)
	{
		pthread_join(pit[i],NULL);
	}
	for(i=0;i<4;i++)
		pthread_mutex_destroy(mutex+i);
}
