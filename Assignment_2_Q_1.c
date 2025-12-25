#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

/* Reads entire file and prints its content */
int readWholeFile(const char *fileName)
{
    int fd;
    int bytesRead;
    int totalBytes = 0;
    char buffer[BUFFER_SIZE];

    fd = open(fileName, O_RDONLY);
    if (fd == -1)
    {
        perror("open failed");
        return -1;
    }

    /* Read until EOF (read() returns 0) */
    while ((bytesRead = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        write(STDOUT_FILENO, buffer, bytesRead);
        totalBytes += bytesRead;
    }

    if (bytesRead == -1)
    {
        perror("read failed");
        close(fd);
        return -1;
    }

    printf("\n\nTotal bytes read: %d\n", totalBytes);

    close(fd);
    return 0;
}

int main()
{
    char fileName[256];

    printf("Enter file name: ");
    scanf("%255s", fileName);

    readWholeFile(fileName);

    return 0;
}