#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>

/*
 * Function Name: checkFileInDirectory
 * ----------------------------------
 * Checks whether a given file exists inside the given directory.
 * If found, prints the absolute path of the matched file.
 */
int check_File_In_Dir(const char *directoryName, const char *fileName)
{
    DIR *directoryPointer;
    struct dirent *directoryEntry;
    char absolutePath[PATH_MAX];

    /*
     * opendir() system call opens the directory stream.
     * Returns pointer to DIR structure on success, NULL on failure.
     */
    directoryPointer = opendir(directoryName);
    if (directoryPointer == NULL)
    {
        perror("Failed to open directory");
        return -1;
    }

    /*
     * readdir() reads directory entries one by one.
     */
    while ((directoryEntry = readdir(directoryPointer)) != NULL)
    {
        if (strcmp(directoryEntry->d_name, fileName) == 0)
        {
        /*
        * realpath() converts relative path to absolute path.
        */
        snprintf(absolutePath, sizeof(absolutePath),"%s/%s", directoryName, fileName);

        if (realpath(absolutePath, absolutePath) != NULL)
        {
            printf("File found at: %s\n", absolutePath);
        }
        else
        {
            perror("Failed to get absolute path");
        }

        closedir(directoryPointer);
        return 0;
        }
    }

    closedir(directoryPointer);
    printf("File not found in the given directory\n");
    return -1;
}

int main()
{
    char directoryName[256];
    char fileName[256];

    printf("Enter directory name: ");
    scanf("%255s", directoryName);

    printf("Enter file name to search: ");
    scanf("%255s", fileName);

    check_File_In_Dir(directoryName, fileName);

    return 0;
}