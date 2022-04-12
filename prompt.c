#include "headers.h"

void prompt_print(paths path, char *name)
{
    struct passwd *user = getpwuid(getuid()); //get user name

    
    if (strcmp(path->home, path->curr) == 0)
        printf("<%s@%s:~>", user->pw_name, name);//if home print ~
    else
        printf("<%s@%s:%s>", user->pw_name, name, path->curr);
   
}
