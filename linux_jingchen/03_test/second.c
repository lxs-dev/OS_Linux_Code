#include "stdio.h"
#include "fcntl.h"
#include "unistd.h"

int main ()
{
    int i=0;
    int ret;
    char change=0;
    ret=open("./myfifo",O_RDONLY);
    if(ret<0)
    {
        printf("open myfifo error\n");
        return -1;
    }
    printf("open myfifo success\n");
    read(ret,&change,1);
    while(change==0);
    for(i=0;i<5;i++)
    {
        printf("i = %d\n",i);
    }
    return 0;
}
