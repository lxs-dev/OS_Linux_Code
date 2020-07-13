#include "stdio.h"
#include "unistd.h"
#include "fcntl.h"

int main(int argc,char *argv[])
{
	int fd;
	char buff[]="qweeasdadsa";
	char read_buff[128];
	int write_ret,read_ret;
	fd = open("./a.c",O_TRUNC|O_RDWR);
	if(fd<0)
		{
			printf("open file a.c failure\n");
			return -1;
		}
	printf("open flie  sucess  fd=%d\n",fd);
	write_ret= write(fd,buff,sizeof(buff));
	printf("write_ret=%d\n",write_ret);

	lseek(fd,0,SEEK_SET);
	read_ret=read(fd,read_buff,sizeof(read_buff));
	printf("read_ret: %d \nread_buff:%s\n",read_ret,read_buff);
	close(fd);
	return 0;
}
