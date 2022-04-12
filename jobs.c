#include "headers.h"

void addjob(int pid, char *name)
{
    joblist[jcount].pid = pid;

    int len = strlen(name) + 1;
    joblist[jcount].name = malloc(len + 1);

    int i;
    for (i = 0; i <= len; i++)
    {
        joblist[jcount].name[i] = name[i];
    }
    joblist[jcount].name[i] = '\0';
    jcount++;
}

void intializejobs()
{
    jcount = 0;
    joblist = (struct jobs *)calloc(sizeof(struct jobs), 100);
}

void jobs(int flag_r, int flag_s)
{

    for (int i = 0; i < jcount; i++)
    {
        char status;
        char stat[10];
        int pid;
        char *file = malloc(20);
        sprintf(file, "/proc/%d/stat", joblist[i].pid);
        if (joblist[i].pid != 0)
        {
            FILE *f;
            char buf[20];
            f = fopen(file, "r");
            if (f != 0)
            {
                fscanf(f, "%d %s %c", &pid, buf, &status);

                fclose(f);

                {
                    if (status == 'R' || status == 'S')
                    {
                        if (flag_s == 0)
                            printf("[%d]  Running %s [%d]\n", i + 1, joblist[i].name, joblist[i].pid);
                    }
                    else if ((status == 'D'))
                    {
                        if (flag_r == 0 && flag_s == 0)
                            printf("[%d]  Sleeping %s [%d]\n", i + 1, joblist[i].name, joblist[i].pid);
                    }
                    else if ((status == 'Z' || status == 'z'))
                    {
                        if (flag_r == 0 && flag_s == 0)
                            printf("[%d]  Zombie %s [%d]\n", i + 1, joblist[i].name, joblist[i].pid);
                    }
                    else if ((status == 'T' || status == 't'))
                    {
                        if (flag_r == 0)
                            printf("[%d]  Stopped %s [%d]\n", i + 1, joblist[i].name, joblist[i].pid);
                    }
                    else
                    {
                        printf("Nostatus");
                        perror("Error");
                    }
                }
            }
        }
    }
}