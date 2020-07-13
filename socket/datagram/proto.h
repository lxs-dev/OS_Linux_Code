#ifndef __PROTO_H
#define __PROTO_H


#include <arpa/inet.h>

#define RECVPORT "1989"
#define NAME_SIZE 11

struct  meg_st
{
	uint8_t name[NAME_SIZE];
	uint32_t math;
	uint32_t chinese;
}__attribute__((packed));


#endif