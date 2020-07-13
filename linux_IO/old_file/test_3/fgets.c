#include "stdio.h"

int main(int argc, char const *argv[])
{
    FILE *scr_fp,*des_fp;
    int scr_ret;
    if(argc<3)
    {
        printf("input error !\n");
        return -1;
    }
    scr_fp=fopen(argv[1],"r");
    if(scr_fp==NULL)
    {
        printf("open scr file error !\n");
        return -2;
    }
    des_fp = fopen(argv[2],"w");
    if(des_fp==NULL)
    {
        printf("open des file error !\n");
        return -3;
    }
    while(1)
    {
        scr_ret = fgetc(scr_fp);
        if(feof(scr_fp))
        {
            printf("put success\n");
            break;
        }
        fputc(scr_ret,des_fp);
    }
    fclose(des_fp);
    fclose(scr_fp);
    return 0;
}
