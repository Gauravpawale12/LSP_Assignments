#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

/* Deletes empty regular files from given directory */
int deleteEmptyFiles(const char *dirName)
{
    DIR *dp;
    struct dirent *de;
    struct stat fileInfo;
    char filePath[512];
    int count = 0;

    dp = opendir(dirName);
    if (dp == NULL)
    {
        perror("opendir failed");
        return -1;
    }

    while ((de = readdir(dp)) != NULL)
    {
        if (!strcmp(de->d_name, ".") || !strcmp(de->d_name, ".."))
            continue;

        /* Build full file path */
        strcpy(filePath, dirName);
        strcat(filePath, "/");
        strcat(filePath, de->d_name);

        if (stat(filePath, &fileInfo) == 0)
        {
            /* Check for regular file of size 0 */
            if (S_ISREG(fileInfo.st_mode) && fileInfo.st_size == 0)
            {
                if (unlink(filePath) == 0)
                {
                    printf("Deleted: %s\n", de->d_name);
                    count++;
                }
            }
        }
    }

    closedir(dp);
    printf("Total empty files deleted: %d\n", count);
    return 0;
}

int main()
{
    char dirName[256];

    printf("Enter directory name: ");
    scanf("%255s", dirName);

    deleteEmptyFiles(dirName);
    return 0;
}