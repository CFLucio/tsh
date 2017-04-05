#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "builtins.h"
#include <ctype.h>

#define MAX_INPUT 1000
#define MAX_ARG 15

/*
    *Parses the shell arguments
*/
void parse_args(char *input, char **args)
{
    for (size_t count = 0; count < MAX_ARG; count++)
    {
        args[count] = strsep(&input, " ");
        if(args[count] == NULL)
            break;
    }
}

/*
    *Execute commands typed in the shell
*/
void execute_arg(char **args)
{
    if (strcmp(args[0], "quit") == 0)
    {
        quit();
    }
    else if (strcmp(args[0], "pwd") == 0)
    {
        pwd();
    }
    else if (strcmp(args[0], "cd") == 0)
    {
        if (args[1] == NULL)
        {
            fprintf(stderr, "*** ERROR: cd requires argument\n");
            return;
        }
        cd(args[1]);
    }
    else if (strcmp(args[0], "fib") == 0)
    {
        if (args[1] == NULL || isalpha(args[1][0]))
        {
            fprintf(stderr, "*** ERROR: fib requires a numeric argument\n");
            return;
        }

        fib(atoi(args[1]));
    }
    else if (strcmp(args[0], "date_time") == 0)
    {
        date_time();
    }
    else if (strcmp(args[0], "help") == 0)
    {
        help();
    }
    else
    {
        pid_t pid = fork();

        if (pid < 0)
        {
            fprintf(stderr, "*** ERROR: fork error\n");
            return;
        }
        // we're on the child
        else if (pid == 0)
        {
            execvp(args[0], args);

            // if execvp returns, an error occurred
            fprintf(stderr, "*** ERROR: error in executing %s\n", args[0]);
            quit();
        }
        // we're on the parent
        else
        {
            int status;
            waitpid(pid, &status, 0);
        }
    }
}

/*
    *Main loop from the shell
    that receives input and controls it
*/
void shell_loop(void)
{
    char input[MAX_INPUT];
    char *arguments[MAX_ARG];

    do
    {
        printf("> ");
        fgets(input, MAX_INPUT, stdin);

        /* the newline is removed from input to
            avoid strcmp mistakes */
        if (input[strlen(input) - 1] == '\n')
        {
            input[strlen(input) - 1] = '\0';
        }

        parse_args(input, arguments);
        execute_arg(arguments);

    } while(*input != EOF && input != NULL);
}