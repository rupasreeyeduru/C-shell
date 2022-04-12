#include "headers.h"
#include <errno.h>
void pinfo(long int id, int flag)
{

    long int pid;
    if (flag == 0)
        pid = (getpid());
    else
        pid = id;

    char status;
    long int size;
    printf("pid --%ld\n", pid);
    char buf[100];
    char *file = malloc(20);
    sprintf(file, "/proc/%ld/stat", pid);

    FILE *f;
    f = fopen(file, "r");
    if (f == 0)
    {
        perror("Error");
    }
    else
    {
        fscanf(f, "%ld %s %c", &pid, buf, &status);
        printf("ProcessStatus --%c\n", status);  //to findout status
        fclose(f);

        sprintf(file, "/proc/%ld/statm", pid);

        f = fopen(file, "r");
        if (f == 0)
        {
            printf("Error");
        }
        else
        {
            fscanf(f, "%ld ", &size);
            printf("memory --%ld\n", size);  // to findout memory
            fclose(f);

            sprintf(file, "/proc/%ld/exe", pid);
            char s[100];
            int n = readlink(file, s, 100); // to findout executable path
            s[n] = '\0';
            printf("Executable Path--%s\n", s);
        }
    }
}
