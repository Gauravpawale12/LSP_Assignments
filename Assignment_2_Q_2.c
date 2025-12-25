#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int writeStringToFile(const char *fileName, const char *data)
{
    int fd;
    int bytesWritten;
    int length;

    /* Open file in append mode, create if not present */
    fd = open(fileName, O_WRONLY | O_APPEND | O_CREAT, 0644);
    if (fd == -1)
    {
        perror("open failed");
        return -1;
    }

    length = strlen(data);

    /* Write string to file */
    bytesWritten = write(fd, data, length);
    if (bytesWritten == -1)
    {
        perror("write failed");
        close(fd);
        return -1;
    }

    printf("Number of bytes written: %d\n", bytesWritten);

    close(fd);
    return 0;
}

int main()
{
    char fileName[256];
    char buffer[1024];

    printf("Enter file name: ");
    scanf("%255s", fileName);
    getchar();   /* consume leftover newline */

    printf("Enter string to write: ");
    fgets(buffer, sizeof(buffer), stdin);

    writeStringToFile(fileName, buffer);

    return 0;
}