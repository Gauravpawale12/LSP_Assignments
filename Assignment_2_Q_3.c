#include <stdio.h>
#include <dirent.h>
#include <string.h>

/* Lists all file and directory names, skipping . and .. */
int listFiles(const char *dirName)
{
    DIR *dir;
    struct dirent *entry;

    dir = opendir(dirName);
    if (dir == NULL)
    {
        perror("opendir failed");
        return -1;
    }

    while ((entry = readdir(dir)) != NULL)
    {
        /* Skip current and parent directory entries */
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0)
            continue;

        printf("%s\n", entry->d_name);
    }

    closedir(dir);
    return 0;
}

int main()
{
    char dirName[256];

    printf("Enter directory name: ");
    scanf("%255s", dirName);

    listFiles(dirName);

    return 0;
}