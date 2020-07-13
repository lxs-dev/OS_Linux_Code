#include "unistd.h"
#include "stdio.h"

int main ()
{
    __pid_t pid;
    int  chang=0;
    int fp[2];
    int ret;
    

    ret=pipe(fp);
    if(ret<0)
    {
      printf("pipe error!\n");
    }
    printf("pipe success %d\n",ret);

    pid=fork();
    
    if(pid==0)
    {
        int i=0;
        read(fp[0],&chang,1);
        while(chang==0);
        for(i=0;i<5;i++)
        {
        printf("child i=%d\n",i);
        usleep(5);
        }
    }
    if(pid>0)
    {
        int i=0;
        for(i=0;i<5;i++)
        {
        printf("parent i=%d\n",i);
        usleep(5);
        }
        chang=1;
        write(fp[1],&chang,1);
        usleep(5000);
    }
    while(1);
    return 0;
}