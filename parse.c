#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int count_tokens(char *line, char symbol) {
    int n = 0;
    int i;
    for (i = 0; line[i]; ++i)
    {
        if(line[i] == symbol){
            ++n; 
        }
    }
    return n + 1; 
}

char **parse_commands(char *line) 
{
    // counts ;s
    int tokens = count_tokens(line, ';');
    char **commands = malloc((tokens) * sizeof(char *)); 
    int i = 0;
    while(commands[i] = strsep(&line, ";")) i++;
    return commands;
}

char **parse_pipes(char *command)
{
    int tokens = count_tokens(command, '|'); 
    char **pipe_args = malloc((tokens) * sizeof(char *)); 
    int i = 0;
    while(pipe_args[i] = strsep(&command, "|")) i++;
    return pipe_args;
}

char **parse_redirs(char *command)
{
    int tokens = count_tokens(command, '>') + count_tokens(command, '<') - 1;
    char **redir_args = malloc((tokens) * sizeof(char *)); 
    int i = 0;
    while(redir_args[i] = strsep(&command, "><")) i++;
    return redir_args; 
}



char **parse_args(char *command) //note that parse_args obliterates the argument, i.e. mutates it. 
{
    // counts spaces
    int tokens = count_tokens(command, ' ');
    // subtracts spaces at beginning and end
    if (command[0] == ' ')
    {
        tokens--;
        strsep(&command, " ");
    }
    if (command[strlen(command) - 1] ==  ' ')
    {
        tokens--;
    }

    char **args = malloc((tokens) * sizeof(char *));
    int i = 0;
    while(i < tokens) 
    { 
        
        args[i] = strsep(&command, " ");
        i++;
    }
    return args;
}






