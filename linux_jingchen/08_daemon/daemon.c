#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FILE_NAME "/tmp/out" 

int daemonnize(void )
{
	pid_t pid;
	int fd;

	pid = fork();
	if(pid<0)
	{
		perror("fork()");
		return -1;
	}
	if(pid>0) exit(0);

	fd = open("/dev/null",O_RDWR);
	if(fd < 0)
	{
		perror("open");
		return -1;
	}
	dup2(fd,0);
	dup2(fd,1);
	dup2(fd,2);
	if(fd>2) 
		close(fd);

	setsid();
	chdir("/");
	return 0;
}

int main()
{

	FILE *fp;
	int i=0;

	if(daemonnize()<0)
	{
		exit(1);
	}
	fp = fopen(FILE_NAME,"w");
	if(fp<0)
	{
		perror("fopen()");
		exit(1);
	}
	for(i=0;;i++)
	{
		fprintf(fp, "%d\n",i );
		fflush(NULL);
		sleep(1);
	}	
	exit(0);
}