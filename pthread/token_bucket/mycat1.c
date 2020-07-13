#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include "tbt.h"
#include "debug.h"

#define CPS 10
#define TOKEN_MAX 100
#define SIZE 1024

int main(int argc,char **argv)
{
	int fds;
	char buf[SIZE];
	int real_size;
	int ret;
	int pos;
	token_t * tk;
	int rsize;
	tk = token_init(CPS,TOKEN_MAX);
	if(tk == NULL)
	{
		fprintf(stderr, "token_init()");
		exit(1);
	}
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
		rsize = GetTokenNum(tk,SIZE);
		if(rsize<0)
		{
			fprintf(stderr, "GetTokenNum()");
			break;
		}
		do
		{
			real_size = read(fds,buf,rsize);
			//debug(real_size);
			if(real_size < 0)
			{
				if(EINTR  == errno ) break;
				perror("read()");
				break;	
			}
		}while(real_size < 0);
		if(real_size == 0 )
		{
			break;
		}

		if(rsize - real_size > 0)
			ReturnTokenNum(tk,(rsize - real_size) );

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
	token_destroy(tk);
	exit(0);
}


