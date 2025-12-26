#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
//#include<string.h>
//#include<sys/stat.h>
#include<unistd.h>
//#include<sys/types.h>

int main(int argc, char *argv[])
{
    
    int fd = 0;
    
    fd = access(argv[1],R_OK | W_OK);


    if(fd < 0)
    {
        //fd = open("Marvellous.txt",0777);
        printf("File is not accessible: %d\n",fd);
        printf("Reason :%s\n",strerror(errno));
        return -1;
    }
    else
    {
        printf("File is acessible with fd : %d\n",fd);
        return 0;
    }

    close(fd);
    return 0;
}