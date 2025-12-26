
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define BUFFER_SIZE 4096

/*
 * Function Name: copy_Filecontents
 * --------------------------------
 * Copies contents of source file to destination file
 * using buffered read() and write() system calls.
 * Destination file is created if it does not exist
 * and truncated if it already exists.
 * Source file permissions are preserved.
 */

int copy_Filecontents(const char *sourceFile, const char *destFile)
{
    int source_fd, dest_fd;
    ssize_t bytes_R, bytes_W;
    char buffer[BUFFER_SIZE];
    struct stat source_File_Info;

    source_fd = open(sourceFile, O_RDONLY);
    if (source_fd == -1)
    {
        perror("Failed to open source file");
        return -1;
    }

    /* Get source file metadata */
    if (stat(sourceFile, &source_File_Info) == -1)
    {
        perror("Failed to get source file information");
        close(source_fd);
        return -1;
    }

    /* Open / create destination file */
    dest_fd = open(destFile, O_WRONLY | O_CREAT | O_TRUNC, source_File_Info.st_mode);
    if (dest_fd == -1)
    {
        perror("Failed to open destination file");
        close(source_fd);
        return -1;
    }

    /* Copy data */
    while ((bytes_R = read(source_fd, buffer, BUFFER_SIZE)) > 0)
    {
        ssize_t totalWritten = 0;

        while (totalWritten < bytes_R)
        {
            bytes_W = write(dest_fd, buffer + totalWritten, bytes_R - totalWritten);

            if (bytes_W == -1)
            {
                perror("Write operation failed");
                close(source_fd);
                close(dest_fd);
                return -1;
            }

            totalWritten += bytes_W;
        }
    }

    if (bytes_R == -1)
    {
        perror("Read operation failed");
        close(source_fd);
        close(dest_fd);
        return -1;
    }

    /* Preserve permissions */
    chmod(destFile, source_File_Info.st_mode);

    close(source_fd);
    close(dest_fd);

    return 0;
}

int main()
{
    char sourceFile[256];
    char destFile[256];

    printf("Enter source file name: ");
    scanf("%255s", sourceFile);

    printf("Enter destination file name: ");
    scanf("%255s", destFile);

    if (copy_Filecontents(sourceFile, destFile) == 0)
    {
        printf("File copied successfully\n");
    }

    return 0;
}