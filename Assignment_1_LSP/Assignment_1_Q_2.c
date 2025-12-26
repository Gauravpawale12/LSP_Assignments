#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>
#include<sys/stat.h>
#include<unistd.h>
#include<sys/types.h>

int main(int argc, char *argv[])
{
    
    int fd = 0;
    
   // fd = open(argv[1],O_RDONLY| O_CREAT);
   // fd = open(argv[1],O_WRONLY| O_CREAT);
   // fd = open(argv[1],O_RDWR| O_CREAT);
    fd = open(argv[1],O_APPEND| O_CREAT);


    if(fd < 0)
    {
        printf("File  NOT opened with fd : %d\n",fd);
        printf("Reason :%s\n",strerror(errno));
        return -1;
    }
    else
    {
        printf("File is successfully opened with fd : %d\n",fd);
        return 0;
    }

    close(fd);
    return 0;
}