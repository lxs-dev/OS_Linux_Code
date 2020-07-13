#include<stdio.h>
#include<unistd.h>
#include <stdlib.h>

#define LEFT 30000000
#define RIGHT 30000200

int main()
{
	int i,j;
	for( i = LEFT ; i < RIGHT ; i++)
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
		if(adc)
			printf("%d is prime\n",i);
	}
		
	
	exit(0);
}