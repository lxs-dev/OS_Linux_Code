#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc ,char**argv)
{
	int fd;
	int ret;
	struct stat file;
	fd = open(argv[1],O_RDONLY);
	if(fd<0)
	{
		perror("open()");
		exit(1);
	}
	ret = fstat(fd,&file);
	
	printf("size = %ld",file.st_size);
	close(fd);
	exit(0);	
}
