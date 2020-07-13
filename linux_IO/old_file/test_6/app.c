#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/types.h>

void fun0(void)
{
	printf("fun0\n");
}
void fun1(void)
{
	printf("fun1\n");
}
int main()
{
	pid_t pid=-1;
	pid_t pid_1=-1;
	printf("***********lxs*************\n");
	fork();
	if(pid==0)
	{
		printf("***********one*************\n");
		//printf("my child pid = %d\n", getpid());
		printf("my child  parent pid = %d\n", getppid());
		//printf("hello world \n");
	}
	if(pid>0)
	{
		sleep(1);
		printf("***********two*************\n");
		printf("my parent pid = %d\n", getpid());
	}
	fork();
	if(pid_1==0)
	{
		printf("***********three*************\n");
		//printf("my child pid = %d\n", getpid());
		printf("my child  parent pid = %d\n", getppid());
		//printf("hello world \n");
	}
	if(pid_1>0)
	{
		sleep(1);
		printf("***********fort*************\n");
		printf("my parent pid = %d\n", getpid());
	}
	printf("my parent pid = %d\n", getppid());
	/*
	//Á·Ï°getpid	getppid
	while(1)
	{
		pid_t pid;
		pid = getpid();
		printf("%d \n",pid);
		pid = getppid();
		printf("%d \n",pid);
		sleep(2);
	}
	*/
	/*
	//Á·Ï° atexit
	int i=0;
	extern char **environ;
	while(environ[i]!=NULL)
	{
		printf("%s \n",environ[i]);
		i++;
	}
	printf("num0\n");
	atexit(fun0);
	atexit(fun1);
	printf("num1\n");
	*/
	return 0;
	//_exit(0);
}