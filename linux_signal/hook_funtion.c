#include<stdio.h>
#include<stdlib.h>

void handler(void)
{
	printf("lxs\n");
}

int main()
{
	printf("********************\n");
	atexit(handler);
	printf("********************\n");
	exit(0);
}
