#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

#define BUF 4096

/* Copy file and delete source */
int copyDelete(const char *src, const char *dst)
{
    int sfd, dfd;
    ssize_t n;
    char buf[BUF];
    struct stat st;

    sfd = open(src, O_RDONLY);
    if (sfd == -1) return -1;

    stat(src, &st);
    dfd = open(dst, O_WRONLY | O_CREAT | O_TRUNC, st.st_mode);
    if (dfd == -1) { close(sfd); return -1; }

    while ((n = read(sfd, buf, BUF)) > 0)
        write(dfd, buf, n);

    close(sfd);
    close(dfd);
    unlink(src);
    return 0;
}

int main()
{
    DIR *dp;
    struct dirent *de;
    struct stat st;
    char srcDir[256], dstDir[256];
    char srcPath[512], dstPath[512];
    int count = 0;

    printf("Enter source directory: ");
    scanf("%255s", srcDir);

    printf("Enter destination directory: ");
    scanf("%255s", dstDir);

    dp = opendir(srcDir);
    if (dp == NULL)
    {
        perror("opendir failed");
        return 1;
    }

    while ((de = readdir(dp)) != NULL)
    {
        if (!strcmp(de->d_name, ".") || !strcmp(de->d_name, ".."))
            continue;

        /* Build source path */
        strcpy(srcPath, srcDir);
        strcat(srcPath, "/");
        strcat(srcPath, de->d_name);

        /* Build destination path */
        strcpy(dstPath, dstDir);
        strcat(dstPath, "/");
        strcat(dstPath, de->d_name);

        if (stat(srcPath, &st) == 0 && S_ISREG(st.st_mode))
        {
            if (rename(srcPath, dstPath) == 0 ||
                copyDelete(srcPath, dstPath) == 0)
                count++;
        }
    }

    closedir(dp);
    printf("Total files moved: %d\n", count);
    return 0;
}