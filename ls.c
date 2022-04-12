#include "headers.h"
#include "time.h"
#include <errno.h>

void ls(char *path, int flag_l, int flag_a)
{
    char filenames[100][100];
    DIR *dir1;
    struct dirent *dir;
    dir1 = opendir(path);

    if (dir1 != NULL)
    {
        dir = readdir(dir1);
        int count = 0;
        long int blockcount = 0;
        if (flag_a == 1)
        {
            while (dir != NULL)
            {
                strcpy(filenames[count], dir->d_name);
                // printf("%s\n", dir->d_name);
                dir = readdir(dir1);
                char *s = malloc(100);
                strcpy(s, path);
                strcat(s, "/");
                strcat(s, filenames[count]);
                struct stat ofile1;
                stat(s, &ofile1);
                blockcount = blockcount + ((ofile1.st_blocks));
                count++;
            }
        }
        else
        {
            while (dir != NULL)
            {
                strcpy(filenames[count], dir->d_name);
                // printf("%s\n", dir->d_name);
                dir = readdir(dir1);
                if (filenames[count][0] != '.')
                {
                    char *s = malloc(100);
                    strcpy(s, path);
                    strcat(s, "/");
                    strcat(s, filenames[count]);

                    struct stat ofile1;
                    stat(s, &ofile1);
                    blockcount = blockcount + ((ofile1.st_blocks));

                    count++;
                }
            }
        }

        if (flag_l == 1)
        {
            printf("total count %ld\n", blockcount / 2);
            for (int i = 0; i < count; i++)
            {
                char *s = malloc(100);
                strcpy(s, path);
                strcat(s, "/");
                strcat(s, filenames[i]);
                struct stat ofile1;
                stat(s, &ofile1);
                char perm[10] = "-rwxrwxrwx";
                //printf("%s\n",s);
                if (S_ISDIR(ofile1.st_mode))
                    perm[0] = 'd';

                if (stat(s, &ofile1) == 0)
                {
                    if ((ofile1.st_mode & S_IRUSR) == 0)
                    {
                        perm[1] = '-';
                    }

                    if ((ofile1.st_mode & S_IWUSR) == 0)
                    {
                        perm[2] = '-';
                    }

                    if ((ofile1.st_mode & S_IXUSR) == 0)
                    {
                        perm[3] = '-';
                    }

                    if ((ofile1.st_mode & S_IRGRP) == 0)
                    {
                        perm[4] = '-';
                    }

                    if ((ofile1.st_mode & S_IWGRP) == 0)
                    {
                        perm[5] = '-';
                    }

                    if ((ofile1.st_mode & S_IXGRP) == 0)
                    {
                        perm[6] = '-';
                    }

                    if ((ofile1.st_mode & S_IROTH) == 0)
                    {
                        perm[7] = '-';
                    }

                    if ((ofile1.st_mode & S_IWOTH) == 0)
                    {
                        perm[8] = '-';
                    }

                    if ((ofile1.st_mode & S_IXOTH) == 0)
                    {
                        perm[9] = '-';
                    }
                }
                struct passwd *pws1;
                pws1 = getpwuid(ofile1.st_uid);
                struct passwd *pws2;
                pws2 = getpwuid(ofile1.st_gid);
                char time[16];
                strftime(time, 16, "%b %2d %I:%M", localtime(&ofile1.st_mtime));

                printf("%s %ld %s %s %ld %s %s\n", perm, ofile1.st_nlink, pws1->pw_name,
                       pws2->pw_name, ofile1.st_size, time, filenames[i]);
            }
        }
        else
        {
            for (int i = 0; i < count; i++)
            {
                printf("%s\n", filenames[i]);
            }
        }
    }

    else
    {

        if (errno == ENOTDIR)

        {
            if (flag_l == 0)
                printf("%s\n", path);
            else

            {
                struct stat ofile1;
                stat(path, &ofile1);
                char perm[10] = "-rwxrwxrwx";

                if (stat(path, &ofile1) == 0)
                {
                    if ((ofile1.st_mode & S_IRUSR) == 0)
                    {
                        perm[1] = '-';
                    }

                    if ((ofile1.st_mode & S_IWUSR) == 0)
                    {
                        perm[2] = '-';
                    }

                    if ((ofile1.st_mode & S_IXUSR) == 0)
                    {
                        perm[3] = '-';
                    }

                    if ((ofile1.st_mode & S_IRGRP) == 0)
                    {
                        perm[6] = '-';
                    }

                    if ((ofile1.st_mode & S_IROTH) == 0)
                    {
                        perm[7] = '-';
                    }

                    if ((ofile1.st_mode & S_IWOTH) == 0)
                    {
                        perm[8] = '-';
                    }

                    if ((ofile1.st_mode & S_IXOTH) == 0)
                    {
                        perm[9] = '-';
                    }
                }
                struct passwd *pws1;
                pws1 = getpwuid(ofile1.st_uid);
                struct passwd *pws2;
                pws2 = getpwuid(ofile1.st_gid);
                char time[16];
                strftime(time, 16, "%b %2d %I:%M", localtime(&ofile1.st_mtime));

                printf("%s %ld %s %s %ld %s %s\n", perm, ofile1.st_nlink, pws1->pw_name,
                       pws2->pw_name, ofile1.st_size, time, path);
            }
        }
        else
            perror("Error");
    }
}
