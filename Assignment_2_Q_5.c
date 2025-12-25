#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>

/* Finds the largest regular file in a directory */
int findLargestFile(const char *dirName)
{
    DIR *dir;
    struct dirent *entry;
    struct stat fileInfo;
    char path[512];

    off_t maxSize = 0;
    char largestFile[256] = "";

    dir = opendir(dirName);
    if (dir == NULL)
    {
        perror("opendir failed");
        return -1;
    }

    while ((entry = readdir(dir)) != NULL)
    {
        /* Skip . and .. */
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(path, sizeof(path), "%s/%s", dirName, entry->d_name);

        if (lstat(path, &fileInfo) == -1)
            continue;

        /* Consider only regular files */
        if (S_ISREG(fileInfo.st_mode))
        {
            if (fileInfo.st_size > maxSize)
            {
                maxSize = fileInfo.st_size;
                strcpy(largestFile, entry->d_name);
            }
        }
    }

    closedir(dir);

    if (strlen(largestFile) == 0)
    {
        printf("No regular files found in directory\n");
        return 0;
    }

    printf("Largest file name : %s\n", largestFile);
    printf("File size         : %ld bytes\n", maxSize);

    return 0;
}

int main()
{
    char dirName[256];

    printf("Enter directory name: ");
    scanf("%255s", dirName);

    findLargestFile(dirName);

    return 0;
}