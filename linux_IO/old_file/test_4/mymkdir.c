#include "stdio.h"
#include "sys/types.h"
#include "dirent.h"

int main(int argc ,char *argv[])
{
    int ret;
    DIR *fd;
    struct dirent *dir;
    if(argc < 2)
    {
        printf("input error !\n");
        return -1;
    }
    fd = opendir(argv[1]);
    if(fd==NULL)
    {
        printf("opendir error\n");
    }
    while(1)
    {
        dir=readdir(fd);
        if(dir!=NULL)
        {
            printf("num: %ld ,name: %s\n",dir->d_ino,dir->d_name);
        }else
        {
            break;
        } 
    }
    closedir(fd);
    return 0;
}
