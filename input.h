#ifndef __INPUT_H
#define __INPUT_H

#include "headers.h"
#include "prompt.h"
struct inputmatrix
{
    char args[1000][100];
    int no_of_args;
};

struct command
{  char com[200];
   int length;

};

struct command* Command;
typedef struct inputmatrix imat;

void take_input(paths path);
void tokenize_input(char *s, paths path);
void execute(struct inputmatrix matrix, int N, paths path,char* command);
void tokenize_commands(char *s, paths path);
#endif
