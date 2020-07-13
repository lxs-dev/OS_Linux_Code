#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>



int main(int argc ,char** argv)
{
	if(argc<2)
	{
		fprintf(stderr,"Usage ........");
		exit(1);	
	}
	int fp = open(argv[1],O_WRONLY|O_CREAT|O_TRUNC,0600);
	if(fp<0)
	{
		perror("open()");
		exit(1);
	}
	lseek(fp,5LL*1024LL*1024LL*1024LL,SEEK_SET);
	write(fp,"",1);
	close(fp);
	exit(0);
}
