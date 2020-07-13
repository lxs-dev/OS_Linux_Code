#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<string.h>
#define PTHNUM 20


void* func(void* p)
{
	char buf[10];
	FILE *fp = fopen("/tmp/out","r+");
	if(fp == NULL)
	{
		perror("fopen()");
		exit(1);
	}
	fgets(buf,10,fp);
	sleep(1);
	fseek(fp,0,SEEK_SET);
	fprintf(fp,"%d\n",(atoi(buf)+1));
	fclose(fp);
	
	pthread_exit(NULL);
}

int main()
{
	pthread_t tid[PTHNUM];
	int i;
	int ret =0 ;
	for(i = 0;i<PTHNUM;i++)
	{
		ret  = pthread_create(tid+i,NULL,func,NULL);
		if(ret)
		{
			fprintf(stderr,"pthread_create(): %s\n", strerror(ret));
			exit(1);
		}
	}

	for(i = 0;i< PTHNUM;i++)
	{
		pthread_join(tid[i],NULL);
	}
	exit(0);	
}
