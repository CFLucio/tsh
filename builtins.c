#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define DIR_MAX 1024

/*
    *Quits the shell
*/
void quit(void)
{
    exit(0);
}

/*
    *Prints the current working directory
*/
void pwd(void)
{
    char curr_dir[DIR_MAX];

    if (getcwd(curr_dir, DIR_MAX) != NULL)
    {
        printf("%s\n", curr_dir);
    }
    else
    {
        fprintf(stderr, "*** ERROR: pwd\n");
    }
}

/*
    *Changes the current directory to dir
*/
void cd(char *dir)
{
    if (dir == NULL)
    {
        fprintf(stderr, "*** ERROR: please, type a directory\n");
        return;
    }

    if ((chdir(dir)) != 0)
    {
        fprintf(stderr, "*** ERROR: invalid cd argument\n");
    }
}

/*
   *Prints max_num first numbers from the
   *Fibonacci sequence starting from 0

   **NOTE: I still need to improve on accepting
   a greater number in fib
*/
void fib(unsigned int max_num)
{
    unsigned long fib_num = 1;
    unsigned long fib_temp = 0;
    size_t count = 0;

    for (; count <= max_num; count++)
    {
        printf("%lu\n", fib_num);
        fib_num += fib_temp;
        fib_temp = fib_num - fib_temp;
    }
}

/*
    *Prints the current date and time
*/
void date_time(void)
{
    time_t curr_time;
    curr_time = time(NULL);
    printf("%s", ctime(&curr_time));
}

/*
    *Prints a short description
    *of each functionality
*/
void help(void)
{
    puts("quit: Quits the shell\npwd: Prints the working directory");
    puts("cd dir: Changes the current directory to dir");
    puts("fib n: Prints the first n numbers from the Fibonacci sequence");
    puts("date_time: Prints the current date and time");
}
