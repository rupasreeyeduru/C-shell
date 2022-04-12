#include "headers.h"
#include <errno.h>

void take_input(paths path)
{

    char input[1000];
    int length = 0;

    char y = (char)getchar();
    input[0] = y;

    while (input[length] != '\n')
    {
        length++;
        input[length] = (char)getchar();
        if (input[length - 1] == '\377')
        {

            exit(0);
        }
    }
    input[length] = 0;
    tokenize_input(&input[0], path);
}

void tokenize_input(char *s, paths path)
{
    char *token = malloc(sizeof(char) * 1000);
    char commands[100][1000];
    token = strtok(s, ";"); //tokenize the input string
    int i = 0;
    
    while (token != NULL) //store the tokenized string in a token matrix
    {
        strcpy(commands[i], token);

        token = strtok(NULL, ";");
        i++;
    }
    for (int j = 0; j < i; j++)
    {
        
        pipeline(commands[j], path);
    }
}

void tokenize_commands(char *s, paths path)
{
    struct inputmatrix matrix;
    
    char *command = malloc(200);
    int j;

    for (j = 0; j <= strlen(s); j++)
    {
        command[j] = s[j];
    }
    command[j] = '\0';
    char *token = malloc(sizeof(char) * 1000);

    token = strtok(&s[0], " ,\t"); //tokenize the input string
    int i = 0;
    while (token != NULL) //store the tokenized string in a token matrix
    {
        strcpy(matrix.args[i], token);
        token = strtok(NULL, " ,\t");
        i++;
    }
    matrix.args[i][0] = '\0';
    matrix.no_of_args = i;

    execute(matrix, matrix.no_of_args, path, command);
}

void execute(struct inputmatrix matrix, int N, paths path, char *command)
{

    for (int i = 0; i < N; i++)
    {
        //  printf("%s\n", matrix.args[i]);
    }

    if (strcmp(matrix.args[0], "cd") == 0)
    {

        cd(matrix, path);
    }
    else if (strcmp(matrix.args[0], "exit") == 0)
    {
        exit(1);
    }
    else if (strcmp(matrix.args[0], "pwd") == 0)
    {

        pwd(path);
    }
    else if (strcmp(matrix.args[0], "ls") == 0)
    {
        char dir[100][100], count = 0, j = 0;
        int l = 0, a = 0;
        for (int i = 1; i < N; i++)
        {
            if (matrix.args[i][0] == '-')
            {
                if (strlen(matrix.args[i]) == 2)
                {
                    if (matrix.args[i][1] == 'a')
                        a = 1;
                    if (matrix.args[i][1] == 'l')
                        l = 1;
                }
                if (strlen(matrix.args[i]) == 3)
                {
                    if (matrix.args[i][1] == 'a' || matrix.args[i][2] == 'a')
                        a = 1;
                    if (matrix.args[i][1] == 'l' || matrix.args[i][2] == 'l')
                        l = 1;
                }
            }
            else
            {
                if (matrix.args[i][0] == '~')
                    strcpy(dir[j], path->home);
                else
                    strcpy(dir[j], matrix.args[i]);

                count++;
                j++;
            }
        }
        if (count == 0)
        {
            strcpy(dir[0], ".");
            j++;
        }
        for (int k = 0; k < j; k++)
        {
            ls(dir[k], l, a);
        }
    }
    else if (strcmp(matrix.args[0], "echo") == 0)
    {

        echo(matrix);
    }

    else if (strcmp(matrix.args[0], "repeat") == 0)
    {
        int count;
        count = (matrix.args[1][0] - '0');

        for (int i = 0; i < N - 2; i++)
        {
            strcpy(matrix.args[i], matrix.args[i + 2]);
        }
        matrix.no_of_args = N - 2;
        for (int i = 0; i < count; i++)
        {
            execute(matrix, N - 2, path, &command[8]);
        }
    }
    else if (strcmp(matrix.args[0], "pinfo") == 0)
    {
        if (N == 1)
            pinfo(-1, 0);
        else
        {
            long int id = atoi(matrix.args[1]);
            pinfo(id, 1);
        }
    }
    else if (strcmp(matrix.args[0], "jobs") == 0)
    {
        if (matrix.no_of_args == 1)
        {
            jobs(0, 0);
        }
        else if (matrix.no_of_args == 2)

        {
            if (strlen(matrix.args[1]) == 2)
            {
                if (matrix.args[1][1] == 'r' && matrix.args[1][0] == '-')
                {
                    jobs(1, 0);
                }
                else if (matrix.args[1][1] == 's' && matrix.args[1][0] == '-')
                {
                    jobs(0, 1);
                }
                else
                {
                    printf("invalid arguments");
                }
            }
            else
            {
                printf("invalid arguments");
            }
        }
        else
        {
            printf("invalid nof arguments");
        }
    }
    else if (strcmp(matrix.args[0], "sig") == 0)
    {
        if (matrix.no_of_args != 3)
            printf("invalid no of args\n");
        else
        {
            Sig(strtol(matrix.args[1], NULL, 10), strtol(matrix.args[2], NULL, 10));
        }
    }
    else if (strcmp(matrix.args[0], "bg") == 0)
    {
        if (matrix.no_of_args != 2)
            printf("invalid no of args\n");
        else
        {
            bg(strtol(matrix.args[1], NULL, 10));
        }
    }
    else if (strcmp(matrix.args[0], "fg") == 0)
    {
        if (matrix.no_of_args != 2)
            printf("invalid no of args\n");
        else
        {
            fg(strtol(matrix.args[1], NULL, 10));
        }
    }
    else

    {
        int i;
        int flag = 0;

        char *args[N + 1];
        int j = 0;
        for (int i = 0; i < N; i++)
        {
            args[i] = malloc(1000);
            if (matrix.args[i][0] == '&')
            {
                flag = 1;
            }
            else
            {
                char *ptr;
                ptr = strchr(matrix.args[i], '&');
                if (ptr)
                {
                    flag = 1;
                    *ptr = 0;
                }
                strcpy(args[j], matrix.args[i]);
                j++;
            }
        }

        for (int k = j; k < N + 1; k++)
        {
            args[k] = NULL;
        }

        exec(args, flag, N, command);
    }

    
}
