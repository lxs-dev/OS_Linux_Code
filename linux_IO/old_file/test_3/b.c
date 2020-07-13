#include "stdio.h"

int main(int argc, char const *argv[])
{
    FILE *scr_fp,*des_fp;
    char scr_ret = 'l';
    int i=0;

    scr_fp=fopen("./a.c","w+");
    if(scr_fp==NULL)
    {
        printf("open scr file error !\n");
        return -2;
    }

    while(i<500000)
    {
        fputc( (int) scr_ret,scr_fp);
        i++;
    }
    fclose(scr_fp);
    return 0;
}