#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>


#define SIZE 10



static volatile int loop = 0;

void alarm_handler(int s)
{
	alarm(1);
	loop = 1;
}
int main(int argc,char **argv)
{
	int fds;
	char buf[SIZE];
	int real_size;
	int ret;
	int pos;
	
	signal(SIGALRM, alarm_handler);
	alarm(1);
	do
	{
		fds = open(argv[1],O_RDONLY);
		if(fds<0)
		{	
			if(EINTR != errno)
			{
				perror("open()");
				exit(1);
			}
		}
	}while(fds < 0);
	
	while(1)
	{

		while(!loop)
			pause();
		do
		{
			real_size = read(fds,buf,SIZE);
			if(real_size < 0)
			{
				if(EINTR  == errno ) break;
				perror("read()");
				break;	
			}
		}while(real_size < 0);
		if(real_size == 0)
		{
			break;
		}
		pos = 0;
		while(real_size>0)
		{
			ret = write(1,buf+pos,real_size);
			if(ret < 0)
			{
				if(errno == EINTR) continue;
				perror("write()");
				break;
			}	
			pos += ret;
			real_size -= ret;
		}
		sleep(1);
	}

	close(fds);
	
	exit(0);
}


