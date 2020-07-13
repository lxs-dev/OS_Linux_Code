#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#if 1
#define Debug debug
#else
#define Debug
#endif
void debug(int i)
{
	printf(" %d\n", i);
}
int getsize(char *argv)
{
	int fd;
	int size;
	fd = open(argv,O_RDONLY);
	if(fd<0)
	{
		perror("open()");
		close(fd);
		return -1;
	}
	size = lseek(fd,0,SEEK_END);

	close(fd);
	return size;
}

int main(int argc , char **argv)
{
	char buf[1];
	char *buf_line = NULL;
	char *buf_line11 = NULL;
	char *test = NULL;
	int fd_1,fd_2;
	int count;
	FILE *fp;
	int ret;
	size_t size;
	int i;
	
	if(argc<3)
	{	
		printf("Usage:%s <file> <line>\n",argv[0] );
		exit(1);
	}
	int f_size = getsize(argv[1]);
	int line_biao = atoi(argv[2]);

	fd_1 = open(argv[1],O_RDWR);
	if(fd_1 < 0)
	{
		perror("open()");
		exit(1);
	}
	fd_2 = open(argv[1],O_RDWR);
	if(fd_2 < 0)
	{
		close(fd_2);
		perror("open()");
		exit(1);
	}

	count = 0;
	while(count != (line_biao-1))
	{
		ret = read(fd_1,buf,1);
		if(ret < 0)
		{
			perror("read()");
			close(fd_1);
			close(fd_2);
			exit(1);
		}
		if(strcmp(buf,"\n")==0)
		count++;
	}

	count = 0;
	while(count != line_biao)
	{
		ret = read(fd_2,buf,1);
		if(ret < 0)
		{
			perror("read()");
			close(fd_1);
			close(fd_2);
			exit(1);
		}
		if(strcmp(buf,"\n")==0)
		count++;
	}
	int f_size1 = lseek(fd_2,0,SEEK_CUR);
	int f_size2 = lseek(fd_1,0,SEEK_CUR);
	for(i=0;i<(f_size-f_size1);i++)
	{
		ret = read(fd_2,buf,1);
		if(ret <0 )
		{
			break;
		}
		write(fd_1,buf,1);
	}
	
	close(fd_2);
	ftruncate(fd_1,f_size-(f_size1-f_size2));
	close(fd_1);
	exit(0);	

}


