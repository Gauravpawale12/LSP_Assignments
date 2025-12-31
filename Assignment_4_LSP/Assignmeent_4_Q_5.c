#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    int fd;
    off_t size;
    char *buffer;
    ssize_t bytes;

    if (argc != 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        printf("Error opening file: %s\n", strerror(errno));
        return 2;
    }

    /* Get file size */
    size = lseek(fd, 0, SEEK_END);
    if (size == -1)
    {
        printf("Error getting file size: %s\n", strerror(errno));
        close(fd);
        return 3;
    }

    /* Move file offset back to start */
    if (lseek(fd, 0, SEEK_SET) == -1)
    {
        printf("Error resetting file offset: %s\n", strerror(errno));
        close(fd);
        return 4;
    }

    buffer = (char *)malloc(size);
    if (buffer == NULL)
    {
        printf("Memory allocation failed: %s\n", strerror(errno));
        close(fd);
        return 5;
    }

    bytes = read(fd, buffer, size);
    if (bytes == -1)
    {
        printf("Error reading file: %s\n", strerror(errno));
        free(buffer);
        close(fd);
        return 6;
    }

    /* Print content in reverse */
    for (off_t i = size - 1; i >= 0; i--)
    {
        write(STDOUT_FILENO, &buffer[i], 1);
    }

    free(buffer);
    close(fd);

    return 0;
}


/*
reversed content from file_1.txt ----> it contains This is File_1
normally conpiled and output is 
1_elif si sihT

*/