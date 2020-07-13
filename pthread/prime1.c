#include<stdio.h>
#include<unistd.h>
#include <stdlib.h>
#include<pthread.h>
#include<string.h>

#define LEFT 30000000
#define RIGHT 30000200
#define THRNUM (RIGHT-LEFT+1)

void *func(void *p);

struct thr_arg
{
	int n;
};

int main()
{
	int i,err;
	pthread_t tid[THRNUM];
	struct thr_arg *p = NULL;
	struct thr_arg *perr = NULL;
	for(i=LEFT;i<RIGHT;i++)
	{	
		p = malloc(sizeof(*p));
		if(p == NULL) 
		{
			perror("malloc()");
			exit(1);
		}
		p->n = i;
		err = pthread_create(tid+i-LEFT,NULL,func,p);
		if(err)
		{
			fprintf(stderr,"err = %s",strerror(err));
			exit(1);
		}
	}

	for(i=LEFT;i<RIGHT;i++)
	{
		pthread_join(perr);
		free(perr);
	}

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
	//	printf("%d is prime\n",i);
	pthread_exit(p);
}
