#include <stdio.h>
#include <stdlib.h>

#define SIZE 1024

int main(int argc, char  **argv)
{
	FILE *fps,*fpd;
	int i;
	char *buf = NULL;
	size_t size =0 ;

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
		if(getline(&buf,&size,fps)<0)
			break;
		fprintf(stdout,"size = %ld\n",size);
		fputs(buf,fpd);
	}
	fclose(fps);
	fclose(fpd);
	exit(0);
}
