#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int out_fd, in_fd;
    char buffer[1024];
    ssize_t bytes_read, bytes_written;
    int i;

    if (argc < 3)
    {
        printf("Usage: %s output_file input_file1 input_file2 ...\n", argv[0]);
        return 1;
    }

    /* Open output file */
    out_fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (out_fd == -1)
    {
        printf("Error opening output file: %s\n", strerror(errno));
        return 1;
    }

    /* Loop through input files */
    for (i = 2; i < argc; i++)
    {
        in_fd = open(argv[i], O_RDONLY);
        if (in_fd == -1)
        {
            printf("Error opening input file %s: %s\n", argv[i], strerror(errno));
            close(out_fd);
            return 1;
        }

        /* Read and write content */
        while ((bytes_read = read(in_fd, buffer, sizeof(buffer))) > 0)
        {
            bytes_written = write(out_fd, buffer, bytes_read);
            if (bytes_written == -1)
            {
                printf("Error writing to output file: %s\n", strerror(errno));
                close(in_fd);
                close(out_fd);
                return 1;
            }
        }

        if (bytes_read == -1)
        {
            printf("Error reading from file %s: %s\n", argv[i], strerror(errno));
            close(in_fd);
            close(out_fd);
            return 1;
        }

        close(in_fd);
    }

    close(out_fd);
    return 0;
}

/*
Created sample input files 
echo "This is file_1" > file_1.txt
echo "This is file_2" > file_2.txt
echo "This is file_3" > file_3.txt
echo "This is file_4" > file_4.txt

on cmd
first compiled normally
then ---> ./Myexe ouput.txt file_1.txt file_2.txt file_3.txt file_4.txt
then cat output.txt
*/