#include "stdio.h"
#include "sys/types.h"
#include "dirent.h"
#include "string.h"
#include "unistd.h"
#include "fcntl.h"

int main() 
{
    
    DIR*dp;
    struct dirent *dir;
    char ser[128]={0};
    char file[128]={0};
    int des_fd,scr_fd;
    char buff[128]={0};
    int ret;
start:    
    printf("please input serve PATH and Directory name\n");
    scanf("%s",ser);  
    dp = opendir(ser);
    if(dp==NULL)
    {
        printf("open server :%s error!\n",ser);
        goto start;
    }
    printf("open server :%s success\n",ser);
    while(1)
    {
        dir = readdir(dp);
        if(dir==NULL)
        {
            break;
        }else
        {    
            printf("num:%ld \t name:%s\t\n",dir->d_ino,dir->d_name);
        } 
    }
    printf("\n Please input your need downlond file \n");
    scanf("%s",file);
    scr_fd = open(strcat(strcat(ser,"/"),file),O_RDONLY);
    if(scr_fd<0)
    {
        printf("open scr_file error\n");
        return -1;
    }
    des_fd = open(file,O_CREAT|O_WRONLY,0777);
    if(des_fd<0)
    {
        printf("open des_file error\n");
        return -2;
    }
    printf("creat file success\n");
    while(1)
    {
        ret=read(scr_fd,buff,128);
        if(ret<128)
        break;
        write(des_fd,buff,128);
    }
    write(des_fd,buff,ret);
    
    close(des_fd);
    close(scr_fd);
    closedir(dp);
    return 0;
}
