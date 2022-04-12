#ifndef __JOBS_H
#define __JOBS_H


void jobs();
struct jobs
{
    char *name;
    int pid;
};

struct jobs *joblist;

void jobs(int flag_r,int flag_s);
void intializejobs();
void addjob(int pid, char *name);
int jcount;

#endif