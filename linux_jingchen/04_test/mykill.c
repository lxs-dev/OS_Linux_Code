#include "stdio.h"
#include "signal.h"
#include "sys/types.h"
#include "stdlib.h"

int main(int argc, char const *argv[])
{
    int pid,sig;
    int ret;
    if(argc<3)
    {
        printf("重新输入\n");
        return -1;
    }
    sig = atoi(argv[1]);
    pid = atoi(argv[2]);

    ret = kill(pid,sig);
    if(ret<0) printf("杀死进程失败\n");

    printf("success\n");
    
    return 0;
}
