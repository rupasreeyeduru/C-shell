#include "headers.h"
#include <stdio.h>
#include <signal.h>
int main()
{  intializejobs();
    signals();
   signal(SIGCHLD,exited_proc);
   paths path = (paths)malloc(sizeof(paths));
   path->home = (char *)malloc(1000 * sizeof(char));
   path->prev = (char *)malloc(1000 * sizeof(char));
   path->curr = (char *)malloc(1000 * sizeof(char));
   getcwd(path->home, 1000);
   getcwd(path->prev, 1000);
   getcwd(path->curr, 1000);
   int fd = open("/proc/sys/kernel/hostname", O_RDONLY);
   char *name = malloc(100 * sizeof(char));
   read(fd, name, 100);
   close(fd);
   int length = strlen(name);

   name[length - 1] = 0;
   while (1)
   { // finishedbg();
      prompt_print(path, name);
      take_input(path);
   }
   return 0;
}
