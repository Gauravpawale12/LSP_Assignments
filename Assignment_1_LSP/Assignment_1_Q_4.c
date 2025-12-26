#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
//#include<string.h>
#include<sys/stat.h>
#include<unistd.h>
//#include<sys/types.h>

int main(int argc, char *argv[])
{
    struct stat sobj;
    unsigned long iRet = 0;
    
    iRet = stat(argv[1],&sobj);

    printf("Size of file : %ld\n",sobj.st_size);
    printf("Inone number : %ld\n",sobj.st_ino);
    printf("ID of device : %ld\n",sobj.st_dev);
    printf("Mode of file : %ld\n",sobj.st_mode);
    printf("Number of Hardlinks :  %ld\n",sobj.st_nlink);
    printf("User ID of owner : %ld\n",sobj.st_uid);
    printf("Group ID of owner : %ld\n",sobj.st_gid);
    printf("User ID of owner : %ld\n",sobj.st_uid);


    close(iRet);
    return 0;
}