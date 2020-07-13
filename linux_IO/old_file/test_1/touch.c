#include "stdio.h"
int main(int argc, char  *argv[])
{
    FILE *fp;
    const char  buf[]="hello linux\n";
    char read_buff[128]={0};

    fp=fopen("./a.c","w+");

    if(fp==NULL)            //等于写成赋值，出现  “段错误（核心以存储）”
   {
        printf("creat file failure\n");
        return -1;
    }
    printf("creat file a.c sucess\n");
    
    fputs(buf,fp);
    fseek(fp,0,SEEK_SET);
    fgets(read_buff,5,fp);
    printf("read_buff:%s",read_buff);
    fgets(read_buff,5,fp);
    printf("read_buff:%s",read_buff);
   // fflush(fp);
   // while(1);
    fclose(fp);
    
    return 0; 
}
