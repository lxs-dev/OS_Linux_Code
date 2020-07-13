#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define SIZE 1024
int main(int argc,char **argv)
{
	int fds,fdd;
	char buf[SIZE];
	int real_size;
	int ret;
	int pos;


	fds = open(argv[1],O_RDONLY);
	if(fds<0)
	{
		perror("open()");
		exit(1);
	}
	printf(" fds = %d \n",fds);
	fdd = open(argv[2],O_WRONLY|O_CREAT);
	if(fdd<0)
	{
		perror("open()");
		close(fds);
		exit(1);
	}
	
	while(1)
	{
		real_size = read(fds,buf,SIZE);
		if(real_size < 0)
		{
			perror("read()");
			break;	
		}
		if(real_size == 0)
		{
			break;
		}
		pos = 0;
		while(real_size>0)
		{
			ret = write(fdd,buf+pos,real_size);
			if(ret < 0)
			{
				perror("write()");
				break;
			}	
			pos += ret;
			real_size -= ret;
		}
	}

	close(fds);
	close(fdd);
	
	exit(0);
}


