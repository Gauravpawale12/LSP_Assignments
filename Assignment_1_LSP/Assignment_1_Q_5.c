/*
Data in file : MY NAME IS GAURAV ANGAD PAWALE WITH RID SOMEETHING.

Output : 
File succesfully opened with fd : 3
10 bytes gets succesfully read
Data from file  : MY NAME IS

*/

#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>
#include<sys/stat.h>
#include<unistd.h>
//#include<sys/types.h>
#define BUFFER_SIZE 100

int main(int argc, char *argv[])
{
   int fd = 0;
   char Buffer[BUFFER_SIZE];
   int iRet = 0;
    
   memset(Buffer, '\0',BUFFER_SIZE);

    fd = open(argv[1],O_RDONLY);

    if(fd < 0)
    {
        printf("Unable to open the file\n");
        printf("Error Name : %s\n",strerror(errno));
        return -1;
    }
    
    
        printf("File succesfully opened with fd : %d\n",fd);

        iRet = read(fd, Buffer, 10);       

        printf("%d bytes gets succesfully read\n",iRet);

        printf("Data from file  : %s\n",Buffer);
    

    close(fd);
    return 0;
}
