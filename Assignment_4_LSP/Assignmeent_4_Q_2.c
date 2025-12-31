#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

#define BUF_SIZE 4096

int main(int argc, char *argv[])
{
    int src_fd, dst_fd;
    off_t offset;
    ssize_t bytes_read, bytes_written;
    char buffer[BUF_SIZE];

    /* Validate arguments */
    if (argc != 4) {
        printf("Usage: %s <source_file> <destination_file> <offset>\n", argv[0]);
        return 1;
    }

    /* Convert offset */
    offset = atoll(argv[3]);
    if (offset < 0) {
        printf("Invalid offset: must be non-negative\n");
        return 1;
    }

    /* Open source file */
    src_fd = open(argv[1], O_RDONLY);
    if (src_fd < 0) {
        printf("Error opening source file: %s\n", strerror(errno));
        return 1;
    }

    /* Open destination file */
    dst_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dst_fd < 0) {
        printf("Error opening destination file: %s\n", strerror(errno));
        close(src_fd);
        return 1;
    }

    /* Move file offset in source file */
    if (lseek(src_fd, offset, SEEK_SET) == (off_t)-1) {
        printf("Error seeking source file: %s\n", strerror(errno));
        close(src_fd);
        close(dst_fd);
        return 1;
    }

    /* Copy data */
    while ((bytes_read = read(src_fd, buffer, BUF_SIZE)) > 0) {
        bytes_written = write(dst_fd, buffer, bytes_read);
        if (bytes_written < 0) {
            printf("Error writing to destination file: %s\n", strerror(errno));
            close(src_fd);
            close(dst_fd);
            return 1;
        }
    }

    if (bytes_read < 0) {
        printf("Error reading source file: %s\n", strerror(errno));
        close(src_fd);
        close(dst_fd);
        return 1;
    }

    /* Clean up */
    close(src_fd);
    close(dst_fd);

    printf("File copied successfully from offset %lld\n", (long long)offset);
    return 0;
}

// gcc Assignment_4_Q_3.c  -o Myexe
// ./Myexe source.txt  dest.txt  12
// output :File copied successfully from offset 12
