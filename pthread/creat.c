#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>
#include<unistd.h>
void* fun(void*p)
{
	puts("pthread working!");
}

int main()
{
	pthread_t tid;
	int err;
	puts("Begin!");
	err = pthread_create(&tid,NULL,fun,NULL);
	if(err)
	{
		fprintf(stderr,"err = %s",strerror(err));	
		exit(1);
	}
	pthread_join(tid,NULL);
	puts("End!");
	exit(0);
}
