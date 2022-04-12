#include "headers.h"

void pipeline(char *s, paths path)
{

    int flides1[2], flides2[2];

    char *token = malloc(sizeof(char) * 1000);
    char commands[100][100];
    token = strtok(s, "|"); //tokenize the input string
    int count = 0;

    while (token != NULL)
    {
        strcpy(commands[count], token);

        token = strtok(NULL, "|");
        count++;
    }

    if (count == 1)
    {
        redirect(s, path); // if no commands seperated by pipe
        return;
    }

    for (int i = 0; i < count; i++)
    {
        int *current_buffer;
        int *other_buffer;
        if (i % 2 == 0)
        {
            current_buffer = flides1; //filling current buffer alternatively with flides1 and flides2
            other_buffer = flides2;
        }
        else
        {
            current_buffer = flides2;
            other_buffer = flides1;
        }
        if (pipe(current_buffer) < 0)
        {
            perror("Error in pipeline:");
            return;
        }
        int Return = fork();
        if (Return < 0)
        {
            perror("error in forking in pipelining");
            return;
        }
        else if (Return == 0)
        {

            if (i < count - 1)
            {
                dup2(current_buffer[1], STDOUT_FILENO); // writing to pipe
            }
            if (i > 0)
            {
                dup2(other_buffer[0], STDIN_FILENO); // reading from previous command output
            }

            redirect(commands[i], path);
            exit(0);
        }
        else
        {
            wait(NULL); //parent process
            if (i > 0)  // if its not first command in pipe close  read fd of previous buffer
                close(other_buffer[0]);
            if (i < count - 1) // if its not last command in pipe close fd  write fd of current buffer
                close(current_buffer[1]);
        }
    }
}
