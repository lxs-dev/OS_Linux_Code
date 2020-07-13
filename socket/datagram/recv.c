#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "proto.h"
#include <unistd.h>

int main(int argc, char const *argv[])
{
	int sd;
	struct sockaddr_in laddr,saddr;
	struct meg_st mes;
	socklen_t saddrlen;
	char saddr_c[40];

	sd = socket(AF_INET,SOCK_DGRAM,0);


	laddr.sin_family = AF_INET;
	laddr.sin_port = htons(atoi(RECVPORT));
	inet_pton(AF_INET,"0.0.0.0",(void*)&(laddr.sin_addr.s_addr));
	bind(sd,(void*)&laddr,sizeof(laddr));

	saddrlen = sizeof(saddr);
	while(1)
	{
		recvfrom(sd,&mes,sizeof(mes),0,(void*)&saddr,&saddrlen);
		uint32_t s_addr = ntohl(saddr.sin_addr.s_addr);
		inet_ntop(AF_INET,&s_addr,saddr_c,40);
		printf("----message---[%s] %d\n",saddr_c,ntohs(saddr.sin_port));
		printf("name:%s\n",mes.name);
		printf("math:%d\n",ntohl(mes.math));
		printf("chinese:%d\n",ntohl(mes.chinese));
	}
	close(sd);
	exit(0);
}