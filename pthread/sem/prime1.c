#include<stdio.h>
#include<unistd.h>
#include <stdlib.h>
#include<pthread.h>
#include<string.h>
#include"mysem.h"

#define LEFT 30000000
#define RIGHT 30000200
#define THRNUM (RIGHT-LEFT+1)
#define N 2

void *func(void *p);

struct thr_arg
{
	int n;
};

static struct sem_st *sem;

int main()
{
	int i,err;
	pthread_t tid[THRNUM];
	struct thr_arg *p = NULL;
	struct thr_arg *perr = NULL;
	//void * perr;
	sem = sem_init(N);
	for(i=LEFT;i<RIGHT;i++)
	{	
		p = malloc(sizeof(*p));
		if(p == NULL) 
		{
			perror("malloc()");
			exit(1);
		}
		p->n = i;
		sem_sub(sem,1);
		err = pthread_create(tid+i-LEFT,NULL,func,p);
		if(err)
		{
			fprintf(stderr,"err = %s",strerror(err));
			exit(1);
		}
	}

	for(i=LEFT;i<RIGHT;i++)
	{
		pthread_join(tid[i-LEFT],&perr);
		free(perr);
	}
	sem_destroy(sem);
	exit(0);

}

void* func(void *p)
{
	int i = ((struct thr_arg *)p)->n;
	int adc = 1;
	int j =0;
	for(j=2;j<(i/2);j++)
	{
		if(i%j==0)
		{
			adc = 0;
			break;
		}
	}
	if(adc)
		printf("%d is prime\n",i);
	sem_add(sem,1);
	pthread_exit(p);
}
