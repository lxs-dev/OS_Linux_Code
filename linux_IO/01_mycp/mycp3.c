#include <stdio.h>
#include <stdlib.h>

#define SIZE 1024

int main(int argc, char  **argv)
{
	FILE *fps,*fpd;
	int i;
	char buf[SIZE];
	int size;

	if(argc < 3)
	{
		fprintf(stdout, "Usage: %s <src> <dest> \n", argv[0] );
		exit(1);
	}

	fps = fopen(argv[1],"r");
	if(fps == NULL)
	{
		perror("fopen()");
		exit(1);	
	}
	fpd = fopen(argv[2],"w");
	if(fpd == NULL)
	{
		perror("fopen");
		exit(1);
	}

	while(1)
	{
		size = fread(buf,1,SIZE,fps);
		printf("%d\n",size);
		if(size<=0)
			break;
		fwrite(buf,1,size,fpd);
	}
	fclose(fps);
	fclose(fpd);
	exit(0);
}
