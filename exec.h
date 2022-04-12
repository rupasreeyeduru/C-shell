#ifndef __EXEC_H
#define __EXEC_H

#include "headers.h"
void exec(char **args, int flag, int N, char *command);


char *process;

void signals();
void bg(int id);
void fg(int id);
void Sig(int pid, int signal);
void Ctrlc();
void Ctrlz();
int procid;
char* procname;
void exited_proc();
#endif
