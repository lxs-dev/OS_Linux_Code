#include<stdio.h>
#include<stdlib.h>


int main(int argc,char **argv)
{
	FILE *fps;
	int count = 0;
	if(argc<2)
	{
		fprintf(stderr,"Usage..............\n");
		exit(1);
	}
	fps = fopen(argv[1],"r");
	if(fps==NULL)
	{
		perror("fopen()");
		exit(0);
	}
	
	while(fgetc(fps)!=EOF)
	{
		count++;
	}

	fprintf(stdout,"count = %d\n",count);
	fclose(fps);
	exit(0);
}
