#include "unistd.h"
#include "stdio.h"

int main ()
{
    int ret;
    long int i=0;
    int fd[2];
    int w_ret;
    char write_buf='h';
    char read_buf[128];

    ret = pipe(fd);
    if(ret<0)
    {
        printf("open pipe failure\n");
        return -1;
    }
    
    printf("出队 fd[0]: %d  入队 fd[1]: %d\n",fd[0],fd[1]);
    while(1)
    {
        w_ret=write(fd[1],&write_buf,sizeof(write_buf));
        i++;
        printf("i=%ld\n",i);
    }
    read(fd[0],read_buf,w_ret);
    printf("read_buf:%s\n",read_buf);
    printf("出队 fd[0]: %d  入队 fd[1]: %d\n",fd[0],fd[1]);

    close(fd[0]);
    close(fd[1]);
    return 0;
}
