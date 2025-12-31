#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
    int source_fd, dest_fd;
    ssize_t bytesRead;
    char buffer[BUFFER_SIZE];

    // Check command line arguments
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <SourceFile> <DestinationFile>\n", argv[0]);
        return 1;
    }

    // Open source file (read-only)
    source_fd = open(argv[1], O_RDONLY);
    if (source_fd == -1)
    {
        perror("Error opening source file");
        return 1;
    }

    // Open/Create destination file (write-only, truncate if exists)
    dest_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd == -1)
    {
        perror("Error opening/creating destination file");
        close(source_fd);
        return 1;
    }

    // Copy data from source to destination
    while ((bytesRead = read(source_fd, buffer, BUFFER_SIZE)) > 0)
    {
        if (write(dest_fd, buffer, bytesRead) != bytesRead)
        {
            perror("Error writing to destination file");
            close(source_fd);
            close(dest_fd);
            return 1;
        }
    }

    if (bytesRead == -1)
    {
        perror("Error reading source file");
        close(source_fd);
        close(dest_fd);
        return 1;
    }

    // Append required line
    const char *extraLine = "\nI am Studying in Marvellous Infosystems\n";
    if (write(dest_fd, extraLine, strlen(extraLine)) == -1)
    {
        perror("Error appending text");
    }

    // Close files
    close(source_fd);
    close(dest_fd);

    printf("File copied successfully.\n");
    return 0;
}


// gcc Assignment_4_Q_3.c  -o Myexe
// ./Myexe source.txt  dest.txt 
// output :File copied successfully.
