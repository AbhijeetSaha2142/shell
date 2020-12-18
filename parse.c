#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

char **parse_commands(char *line) 
{
    char **commands = malloc(6 * sizeof(char *));
    int i = 0;
    while(commands[i] = strsep(&line, ";")) i++;
    return commands;
}

char **parse_args(char *command) //note that parse_args obliterates the argument.
{
    // counts spaces
    int spaces = 0;
    int i;
    for (i = 0; command[i]; ++i)
    {
        if (command[i] == ' '){
            ++spaces;
        }
    }
    // subtracts spaces at beginning and end
    if (command[0] == ' ')
    {
        spaces--;
        strsep(&command, " ");
    }
    if (command[strlen(command) - 1] ==  ' ')
    {
        spaces--;
    }

    char **args = malloc((spaces + 2) * sizeof(char *));
    i = 0;
    while(i < spaces + 1) 
    { 
        
        args[i] = strsep(&command, " ");
        i++;
    }
    return args;
}

void run(char **args) 
{
    //arg[0] is program, everything else arguments
    int f = fork();

    if (!f) {// child
        execvp(args[0], args);
    } 
    
    if (f) //parent 
    {
        int status;
        int pid = wait(&status); 
    }
}

void run_commands(char **commands) 
{
    int i = 0;
    while(commands[i]) {
        run(parse_args(commands[i]));
        printf("\n");
        i++;
    }
}

void print_string_array(char **input) {
    int i = 0;
    while(input[i]) {
        printf("[%s] ", input[i]); 
        i++;
    }
    printf("\n");
}

int main1()
{
    char test[] = "ls -a -l ; cat makefile";
    char **test_commands = parse_commands(test);
    printf("commands: \n");
    print_string_array(test_commands);

    /*
    printf("args for ls -a -l:  \n");
    char **test_args0 = parse_args(test_commands[0]); 
    print_string_array(test_args0);

    printf("args for cat makefile:  \n");
    char **test_args1 = parse_args(test_commands[1]); 
    print_string_array(test_args1);
    */
    printf("ls -a -l ; cat makefile test:\n");
    run_commands(test_commands);
}






