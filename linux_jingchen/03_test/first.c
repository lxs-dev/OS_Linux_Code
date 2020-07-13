#include "stdio.h"
#include "unistd.h"
#include "fcntl.h"


int main()
{
    int i=0;
    int ret=0;
    char change;
    //printf("lxs");
    ret = open("./myfifo",O_WRONLY);
    
    if(ret<0)
    {
        printf("myfifo error\n");
        return -1;
    }
    printf("open myfifo success\n");

    for(i=0;i<5;i++)
    {
        printf("i = %d,\n",i);
    }
    change =1;
    sleep(5);
    write(ret,&change,1);
    while(1);
    return 0;
}