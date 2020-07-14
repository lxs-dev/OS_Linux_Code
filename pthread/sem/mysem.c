#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "mysem.h"

struct sem_st
{
	int val;
	pthread_mutex_t mutex;
	pthread_cond_t cond;

};

sem_t* sem_init(int val)
{
	struct sem_st *sem;
	sem = malloc(sizeof(*sem));
	if(sem ==NULL)
		return NULL;
	sem->val = val;
	pthread_mutex_init(&sem->mutex,NULL);
	pthread_cond_init(&sem->cond,NULL);
	return sem;
}

int sem_add(sem_t*st,int val)
{
	struct sem_st *sem = st; 
	if(val<=0) return -1;
	pthread_mutex_lock(&sem->mutex);
	sem->val += val;
	pthread_cond_broadcast(&sem->cond);
	pthread_mutex_unlock(&sem->mutex);
	return 0;
}

int sem_sub(sem_t*st,int val)
{
	struct sem_st *sem = st; 
	if(val<=0) return -1;
	pthread_mutex_lock(&sem->mutex);
	while(sem->val < val)
	pthread_cond_wait(&sem->cond,&sem->mutex);
	sem->val -= val;
	pthread_mutex_unlock(&sem->mutex);
	return 0;
}

int sem_destroy(sem_t* st)
{
	struct sem_st *sem = st;
	pthread_mutex_destroy(&sem->mutex);
	pthread_cond_destroy(&sem->cond);
	free(sem);
}
