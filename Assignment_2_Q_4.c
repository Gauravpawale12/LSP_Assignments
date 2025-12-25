#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

/* Prints file type based on st_mode */
void printFileType(mode_t mode)
{
    if (S_ISREG(mode))
        printf("Regular");
    else if (S_ISDIR(mode))
        printf("Directory");
    else if (S_ISLNK(mode))
        printf("Symbolic Link");
    else if (S_ISFIFO(mode))
        printf("FIFO");
    else if (S_ISSOCK(mode))
        printf("Socket");
    else if (S_ISCHR(mode))
        printf("Character Device");
    else if (S_ISBLK(mode))
        printf("Block Device");
    else
        printf("Unknown");
}

/* Lists files with their types */
int listFilesWithType(const char *dirName)
{
    DIR *dir;
    struct dirent *entry;
    struct stat fileInfo;
    char path[512];

    dir = opendir(dirName);
    if (dir == NULL)
    {
        perror("opendir failed");
        return -1;
    }

    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(path, sizeof(path), "%s/%s", dirName, entry->d_name);

        if (lstat(path, &fileInfo) == -1)
        {
            perror("lstat failed");
            continue;
        }

        printf("%-20s : ", entry->d_name);
        printFileType(fileInfo.st_mode);
        printf("\n");
    }

    closedir(dir);
    return 0;
}

int main()
{
    char dirName[256];

    printf("Enter directory name: ");
    scanf("%255s", dirName);

    listFilesWithType(dirName);

    return 0;
}