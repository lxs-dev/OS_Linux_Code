#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<string.h>
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
static int num;
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
	
		pthread_mutex_lock(&mutex);
		while(num != n)
		{
			pthread_cond_wait(&cond,&mutex);
		}
		write(1,&c,1);
		num = next(num);
		pthread_cond_broadcast(&cond);
		pthread_mutex_unlock(&mutex);
	}
	pthread_exit(NULL);
}

int main()
{
	int i = 0,ret=0;
	pthread_t pit[4];
	for(i = 0;i < 4;i++)
	{
		ret = pthread_create(pit+i,NULL,func,(void*)i);
		if(ret)
		{
			fprintf(stderr,"pthread_create(): %s",strerror(ret));
			exit(1);
		}
	}
	for(i=0;i<4;i++)
	{
		pthread_join(pit[i],NULL);
	}
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);
}
