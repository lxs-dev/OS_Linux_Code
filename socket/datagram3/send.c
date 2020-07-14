#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "proto.h"
#include <string.h>
#include <unistd.h>
#include <net/if.h>
int main(int argc, char const *argv[])
{

	int sd;
	struct meg_st message;
	struct sockaddr_in d_addr;

	sd = socket(AF_INET,SOCK_DGRAM,0);
	if(sd < 0)
	{
		perror("socket");
		exit(1);
	}

	struct ip_mreqn mreqn;
	inet_pton(AF_INET,MUGROP,&mreqn.imr_multiaddr);
	inet_pton(AF_INET,"0.0.0.0",&mreqn.imr_address);
	mreqn.imr_ifindex = if_nametoindex("ens33");
	int ret = setsockopt(sd, IPPROTO_IP, IP_MULTICAST_IF,&mreqn, sizeof(mreqn));
	if(ret<0)
	{
		perror("setsockopt()");
		exit(1);
	}
	//bind();
	memcpy(message.name,"lxs",NAME_SIZE);
	message.math = htonl(85);
	message.chinese = htonl(120);

	d_addr.sin_family = AF_INET;
	d_addr.sin_port = htons(atoi(RECVPORT));
	inet_pton(AF_INET,MUGROP,&d_addr.sin_addr.s_addr);
	sendto(sd,&message,sizeof(message),0,(void*)&d_addr,sizeof(d_addr));

	close(sd);
	exit(0);
}