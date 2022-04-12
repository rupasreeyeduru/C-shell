#include "headers.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
int jcount;
void exec(char **args, int flag, int N, char *command)
{
    procname = command;
    int Return = fork();

    if (Return == 0)
    { //child process
        printf("%d", Return);
        int d = execvp(args[0], args);
        setpgid(0, 0); // sets pid of caller as pgid of it.
        if (d < 0)
        {
            perror("error");
            printf("or Command not found\n");
        }
        exit(0);
    }
    else
    { //parent waits if it is a foreground process
        procid = Return;
       
        if (flag == 0)
        {
            signal(SIGTTIN, SIG_IGN);
            signal(SIGTTOU, SIG_IGN);
            setpgid(Return, 0);
            tcsetpgrp(0, __getpgid(Return)); //gives terminal control to processes with pgid Return
            //printf("1.%d\n", __getpgid(Return));
            int status;

            int x = waitpid(Return, &status, WUNTRACED);
            //printf("1.%d\n", getpgrp());
            tcsetpgrp(0, getpgrp()); //gives terminal control back to parent group
            //printf("%d %d\n", getpid(), Return);
            signal(SIGTTIN, SIG_DFL);
            signal(SIGTTOU, SIG_DFL);
        }
        else
        {

            printf("%d", Return);
            setpgid(Return, 0);
            tcsetpgrp(0, getpgrp());
        }
         addjob(Return, command); // adding job to joblist
    }
}



void Sig(int id, int signal)
{
    if (id > jcount || id <= 0)
    {
        perror("No such job");
    }
    else
    {
    
        kill(joblist[id - 1].pid, signal);
    }
}

void bg(int id)
{

    if ((id > jcount) || id <= 0)
    {
        printf("%d %d", id, jcount);
        perror("No such job or ERRor");
        return;
    }
    kill(joblist[id - 1].pid, SIGTTIN); //to read from terminal
    kill(joblist[id - 1].pid, SIGCONT); //makes the process continue if it is stopped
}

void fg(int id)
{

    if ((id > jcount) || id <= 0)
    {
        printf("%d %d", id, jcount);
        perror("No such job or ERRor");
        return;
    }

    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
    tcsetpgrp(0, joblist[id - 1].pid); //gives terminal control to processes with pgid as given pid
    kill(joblist[id - 1].pid, SIGCONT); // continues the process

    int status;
    procid = joblist[id - 1].pid;
    waitpid(joblist[id - 1].pid, &status, WUNTRACED); // wait for process to complete as it is made fg process

    tcsetpgrp(0, getpgrp());  // gives terminal control back
    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);
}
void Ctrlc()
{
    if (procid > 0 && procid != getpid())
        raise(SIGINT);
    // printf("received-c");
}

void Ctrlz()
{
    if (procid > 0 && procid != getpid())
        raise(SIGTSTP);
    // printf("received-z");
}

void signals()
{
    procid = -1;

    signal(SIGINT, Ctrlc);
    signal(SIGTSTP, Ctrlz);
}

void exited_proc()
{
    int status;
    int pid = waitpid(-1, &status, WNOHANG);
    if (pid <= 0)
        return;
    if (WIFEXITED(status))
    {
        printf("\n%s with pid %d exited normally ", procname, pid);
    }
    else
        printf("\n%s with pid %d exited abnormally", procname, pid);

        fflush(stdout);
}
