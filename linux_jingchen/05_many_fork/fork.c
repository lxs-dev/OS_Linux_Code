#include<stdio.h>
#include<unistd.h>
#include <stdlib.h>

int main()
{
	pid_t pid;
	printf("[%d] is start\n",getpid());
	//fflush(NULL);
	pid = fork();
	if(pid < 0)
	{
		perror("fork()");
	}
	if(pid == 0) //child
	{
		printf("[%d]: child is start\n",getpid());
	}else
	{
		printf("[%d]: parent is start\n",getpid());
	}
	printf("[%d] is end\n",getpid());
	getchar();
	exit(0);
}
