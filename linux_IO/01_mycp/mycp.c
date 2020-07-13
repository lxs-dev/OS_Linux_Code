#include <stdio.h>
#include <stdlib.h>

int main(int argc, char  **argv)
{
	FILE *fps,*fpd;
	int i;

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
		i = fgetc(fps);
		fputc(i,stdout);
		if(i == EOF)
			break;
		fputc(i,fpd);
	}
	fclose(fps);
	fclose(fpd);
	exit(0);
}
