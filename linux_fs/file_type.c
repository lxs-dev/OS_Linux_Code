#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
int main(int argc ,char **argv)
{
	int fd;
	struct stat statret;
	if(argc<2)
	{
		printf("Usage ......");
		exit(0);
	}
	fd = open(argv[1],O_RDONLY);
	if(fd<0)
	{
		perror("open()");
		exit(1);
	}
	fstat(fd, &statret);
	printf("type:%o\n",statret.st_mode);
	close(fd);
	
	exit(0);
}
