#ifndef __PROMPT_H
#define __PROMPT_H

#include "headers.h"

struct paths
{
    char *home;
    char *prev;
    char *curr;
};

typedef struct paths *paths;

void prompt_print(paths path, char *name);

#endif
