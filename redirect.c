#include "headers.h"

void redirect(char *s, paths path)
{
    int flag_r = 0; //read
    int flag_w[2];  //write and append
    flag_w[1] = flag_w[0] = 0;
    int j;
    int len = strlen(s);
    int len_1 = 0;
    int k1, k2;
    char *file1;
    file1 = calloc(100, sizeof(char));
    char *file2;
    file2 = calloc(100, sizeof(char));
    int in = 0, out = 0;
    for (j = 0; j < len; j++)
    {
        if (s[j] == '<')
        {

            {

                flag_r = 1;
                k1 = 0;
                out = 0;
                in = 1;
            }
        }
        else if (s[j] == '>')
        {

            if (s[j + 1] == '>')
            {
                flag_w[1] = 1;
                j++;
            }
            else
                flag_w[0] = 1;
            k2 = 0;
            in = 0;
            out = 1;
        }
        else if (in == 1)
        {
            if (s[j] != ' ')
            {
                
                file1[k1] = s[j];
                k1++;
            }
        }
        else if (out == 1)
        {
            if (s[j] != ' ')
            {
                
                file2[k2] = s[j];
                k2++;
            }
        }
        else
            len_1++;
    }

    s[len_1] = 0; // len_1 length of command

    if (flag_r == 1 || flag_w[0] == 1 || flag_w[1] == 1)
    {

        int fd1 = -1, fd2 = -1;
        int dupin = dup(STDIN_FILENO);
        int dupout = dup(STDOUT_FILENO);
        if (flag_r == 1) //read
        {

            fd1 = open(file1, O_RDONLY, 0644);
            if (fd1 < 0)
            {
                perror("error reading input file");
                return;
            }
            dup2(fd1, STDIN_FILENO);
        }
        if (flag_w[0] == 1) //write
        {
            fd2 = open(file2, O_CREAT | O_WRONLY | O_TRUNC, 0644);
            if (fd2 < 0)
            {
                perror("error writing to file");
                return;
            }

            dup2(fd2, STDOUT_FILENO);
        }
        if (flag_w[1] == 1) //append
        {
            fd2 = open(file2, O_CREAT | O_WRONLY | O_APPEND, 0644);
            if (fd2 < 0)
            {
                perror("error  writing to output file");
                return;
            }

            dup2(fd2, STDOUT_FILENO);
        }
        tokenize_commands(s, path);
        if (fd1 > 0)
        {
            close(fd1);
            dup2(dupin, STDIN_FILENO);
        }
        if (fd2 > 0)
        {
            close(fd2);
            dup2(dupout, STDOUT_FILENO);
        }
        return;
    }
    tokenize_commands(s, path);
}
