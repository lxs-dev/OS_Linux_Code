#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"

int main ()
{
    int ret;
    ret  = mkfifo("./myfifo",0777);
    if(ret<0)
    {
        printf("creat pipe_file error !\n");
        return -1;
    }
    printf("creat pipe_file success !\n");

    return 0;
}