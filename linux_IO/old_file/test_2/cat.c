#include "stdio.h"

int main(int argc, char const *argv[])
{
    FILE *fp;
    int read_ret;
    if(argc<2)
    {
        printf("intput error !\n");
        return -2;
    }
    fp = fopen(argv[1],"r");
    if(fp==NULL)
    {
        printf("open file failure\n");
        return -1;
    }

    while(1)
    {
       read_ret = fgetc(fp);
        if(feof(fp))
        {
            //printf("read file end\n");
            return 0;
        }
       fputc(read_ret,stdout);
    }

    fclose(fp);
    return 0;
}
