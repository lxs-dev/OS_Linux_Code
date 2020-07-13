#include<stdio.h>
#include<unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>


#define LEFT 30000000
#define RIGHT 30000200
#define N 3
int main()
{
	int i,j,k;
	pid_t pid;
	for(k=0;k<N;k++)
	{
		pid = fork();
		if(pid<0) 
		{
			perror("fork()");
			exit(0);
		}
		if(pid == 0)
		{
			for( i = LEFT+k ; i < RIGHT ; i+=N)
			{
				int adc = 1;
				for(j=2;j<(i/2);j++)
				{
					if(i%j==0)
					{
						adc = 0;
						break;
					}
				}
				if(adc);
	//				printf("[%d]%d is prime\n",k,i);
				
			}
			exit(0);
		}
	}
	
	
	for(k=0;k<N;k++)
		wait(NULL);
	
	exit(0);
}
