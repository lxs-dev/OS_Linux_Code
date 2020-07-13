#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
*创建子进程，子进程摇身一变成别的程序，但进程的pid号不变，父进程等待子进程完成替他回收资源
*/

int main(int argc, char const *argv[])
{

	pid_t pid;
	puts("Begin!");
	fflush(NULL);
	pid = fork();
	if(pid<0)
	{
		perror("fork()");
		exit(1);
	}

	if(pid==0)
	{
		fflush(NULL);
		execl("/bin/date","date","+%s",NULL);
		perror("exec");
		exit(1);
	}

	wait(NULL);
	puts("End!");
	exit(0);	
}