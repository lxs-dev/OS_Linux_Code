#ifndef __PROTO_H
#define __PROTO_H


#include <arpa/inet.h>

#define RECVPORT "1989"
#define NAME_SIZE (512-8-8)

struct  meg_st
{
	uint32_t math;
	uint32_t chinese;
	uint8_t name[1];
}__attribute__((packed));


#endif