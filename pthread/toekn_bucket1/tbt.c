#include<stdio.h>
#include<stdlib.h>
#include "tbt.h"
#include <signal.h>
 #include <unistd.h>
 #include "debug.h"
#include<pthread.h>
typedef void (*sighandler_t)(int);

struct token_ts
{
	int cps;
	int token;
	int token_max;
	int subscript;
	pthread_mutex_t mutex_t_token;
	pthread_cond_t cond;
};

static struct token_ts *token[NUM_MAX];
static int alarm_flag = 0;
static sighandler_t alarm_hardler_save;
static pthread_mutex_t mutex_token = PTHREAD_MUTEX_INITIALIZER;
pthread_once_t once_control = PTHREAD_ONCE_INIT;
static pthread_t alarm_thread;

void *alarm_hardler(void* p)
{
	int i = 0;
	while(1)
	{
		for(i = 0;i < NUM_MAX;i++)
			if(token[i] != NULL)
			{
				pthread_mutex_lock(&token[i]->mutex_t_token);
				token[i]->token += token[i]->cps;
				if(token[i]->token > token[i]->token_max)
					token[i]->token = token[i]->token_max;
				pthread_cond_broadcast(&token[i]->cond);
				pthread_mutex_unlock(&token[i]->mutex_t_token);
			};
		sleep(1);
	}
	pthread_exit(NULL);
}

void alarm_exit(void)
{
	
	pthread_cancel(alarm_thread);
	pthread_join(alarm_thread,NULL);
	for(int i = 0;i < NUM_MAX;i++)
	{
		if(token[i] != NULL)
		{
			free(token[i]);
		}
	}
}
void alarm_init(void)
{
	pthread_create(&alarm_thread,NULL,alarm_hardler,NULL);
	atexit(alarm_exit);
}
int GetTokenSubscript()
{
	int i = 0;
	for(i = 0;i < 1024 ;i++)
	{
		if(token[i]==NULL)
			return i;
	}
	return -1;
}

token_t *token_init(int cps,int token_max)
{
	struct token_ts *me;
	int i;//

	
	pthread_once(&once_control,alarm_init);
	me = malloc(sizeof(*me));
	if(me == NULL)
		return NULL;
	me ->cps = cps;
	me ->token = 0;
	me ->token_max = token_max;
	me ->subscript = i;
	pthread_mutex_init(&me->mutex_t_token,NULL);
	pthread_cond_init(&me->cond,NULL);
	pthread_mutex_lock(&mutex_token);
	i = GetTokenSubscript();
	if(i < 0)
	{
		free(me);
		return NULL;
	}
	token[i] = me;
	pthread_mutex_unlock(&mutex_token);
	return me;
}
int min(int a,int b)
{
	if(a > b)
		a = b;
	return a;
}
int GetTokenNum(token_t* tk,int want_num)
{
	struct token_ts *me = tk;
	int ret_num; 
	if(want_num <= 0)
		return -1;
	pthread_mutex_lock(&me->mutex_t_token);
	while(me -> token <= 0)
	{
	//	pthread_mutex_unlock(&me->mutex_t_token);
	//	sched_yield(); 
	//	pthread_mutex_lock(&me->mutex_t_token);
		pthread_cond_wait(&me->cond,&me->mutex_t_token);
	}
	ret_num = min(me -> token,want_num);
	me -> token -= ret_num;
	
	pthread_mutex_unlock(&me->mutex_t_token);
	return ret_num;
}
int ReturnTokenNum(token_t* tk ,int ret_num)
{
	struct token_ts *me = tk;
	if(ret_num <= 0)
	{
		return -1;
	}
	pthread_mutex_lock(&me->mutex_t_token);
	me -> token += ret_num;
	if(me ->token > me->token_max)
		me -> token = me->token_max;
	pthread_mutex_unlock(&me->mutex_t_token);
	return ret_num;
}
void token_destroy(token_t *tk)
{
	struct token_ts *me = tk;
	pthread_mutex_lock(&mutex_token);
	pthread_cond_destroy(&me->cond);
	pthread_mutex_destroy(&me->mutex_t_token);
	token[me->subscript] = NULL;
	free(me);
	pthread_mutex_unlock(&mutex_token);
}
/*
pthread_mutex_lock(&mutex_token);
pthread_mutex_unlock(&mutex_token);
pthread_mutex_lock(&me->mutex_t_token);
pthread_mutex_unlock(&me->mutex_t_token);
*/
