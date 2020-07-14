#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "proto.h"
#include <string.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{

	int sd;
	struct meg_st *message;
	struct sockaddr_in d_addr;
	int size=0;
	if(argc<3)
	{
		printf("Usage............\n");
		exit(1);
	}
	if(strlen(argv[2])>NAME_SIZE)
	{
		printf("Name length too long! \n");
		exit(1);
	}
	size = sizeof(*message) + strlen(argv[2]);
	message = malloc(size);
	if(message==NULL)
	{
		perror("malloc()");
		exit(1);
	}
	sd = socket(AF_INET,SOCK_DGRAM,0);
	if(sd < 0)
	{
		perror("socket");
		exit(1);
	}
	//bind();
	memcpy(message->name,argv[2],size);
	message->math = htonl(85);
	message->chinese = htonl(120);

	d_addr.sin_family = AF_INET;
	d_addr.sin_port = htons(atoi(RECVPORT));
	inet_pton(AF_INET,argv[1],&d_addr.sin_addr.s_addr);
	sendto(sd,message,size,0,(void*)&d_addr,sizeof(d_addr));

	close(sd);
	exit(0);
}
