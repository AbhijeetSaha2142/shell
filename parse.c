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
    // counts ;s
    int semis = 0;
    int i;
    for (i = 0; line[i]; ++i)
    {
        if (line[i] == ';'){
            ++semis;
        }
    }
    char **commands = malloc((semis + 1) * sizeof(char *)); 
    i = 0;
    while(commands[i] = strsep(&line, ";")) i++;
    return commands;
}

char **parse_pipes(char *command)
{
    // counts pipes
    int pipes = 0;
    int i;
    for (i = 0; command[i]; ++i)
    {
        if (command[i] == '|'){
            ++pipes;
        }
    }

    char **pipe_args = malloc((pipes + 1) * sizeof(char *)); 
    i = 0;
    while(pipe_args[i] = strsep(&command, "|")) i++;
    return pipe_args;
}
char **parse_in(char *command)
{

}

char **parse_out(char *command)
{

}

char **parse_args(char *command) //note that parse_args obliterates the argument, i.e. mutates it. 
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






