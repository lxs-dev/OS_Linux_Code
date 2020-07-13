#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>
#include<unistd.h>

void fun_clean(void *p)
{
	puts(p);
}
void* fun(void*p)
{
	pthread_cleanup_push(fun_clean,"lxs_1");
	pthread_cleanup_push(fun_clean,"lxs_2");
	pthread_cleanup_push(fun_clean,"lxs_3");
	puts("pthread working!");
	
	pthread_cleanup_pop(1);
	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);
	pthread_exit(NULL);
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
