#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>

#define BUFFER_SIZE 4096

int main(int argc, char *argv[])
{
    int src_fd, dest_fd;
    ssize_t bytes_read, bytes_written;
    off_t offset = 0;
    char buffer[BUFFER_SIZE];

    if (argc != 3) {
        printf("Usage: %s <source_file> <destination_file>\n", argv[0]);
        return 1;
    }

    /* Open source file */
    src_fd = open(argv[1], O_RDONLY);
    if (src_fd == -1) {
        printf("Error opening source file: %s\n", strerror(errno));
        return 1;
    }

    /* Open destination file */
    dest_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd == -1) {
        printf("Error opening destination file: %s\n", strerror(errno));
        close(src_fd);
        return 1;
    }

    /* Copy loop using pread and pwrite */
    while (1) {
        bytes_read = pread(src_fd, buffer, BUFFER_SIZE, offset);
        if (bytes_read == -1) {
            printf("Error reading source file: %s\n", strerror(errno));
            close(src_fd);
            close(dest_fd);
            return 1;
        }

        if (bytes_read == 0) {
            /* End of file */
            break;
        }

        bytes_written = pwrite(dest_fd, buffer, bytes_read, offset);
        if (bytes_written == -1) {
            printf("Error writing destination file: %s\n", strerror(errno));
            close(src_fd);
            close(dest_fd);
            return 1;
        }

        offset += bytes_read;
    }

    close(src_fd);
    close(dest_fd);

    printf("File copied successfully.\n");
    return 0;
}


// gcc Assignment_4_Q_3.c  -o Myexe
// ./Myexe source.txt  new_dest.txt
// output :File copied successfully.