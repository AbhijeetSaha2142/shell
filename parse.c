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

char *trim(char *str) {
    char *end;

    while(*str ==  ' ') str++; 
    end = str + strlen(str) - 1;
    while(end > str && *end == ' ') end--;
    *(end+1) = '\0';
    return str;
}

char **parse_commands(char *line)
{
    // counts ;
    int tokens = count_tokens(line, ';');
    char **commands = malloc((tokens + 1) * sizeof(char *));
    int i = 0;
    while(commands[i] = strsep(&line, ";")) i++;
    commands[tokens] = '\0';
    return commands;
}

char **parse_pipes(char *command)
{
    int tokens = count_tokens(command, '|');
    char **pipe_args = malloc((tokens + 1) * sizeof(char *));
    int i = 0;
    while(pipe_args[i] = strsep(&command, "|")) i++;
    pipe_args[tokens] = '\0';
    return pipe_args;
}

char **parse_redirs(char *command)
{
    int tokens = count_tokens(command, '>') + count_tokens(command, '<') - 1;
    char **redir_args = malloc((tokens + 1) * sizeof(char *));
    int i = 0;
    while(redir_args[i] = strsep(&command, "><")) i++;
    redir_args[tokens] = '\0';
    return redir_args;
}

char *parse_redirs2(char *command)
{
    int tokens = count_tokens(command, '>') + count_tokens(command, '<') - 1;
    if (tokens < 1) return NULL;
    char *redir_args2 = malloc((tokens + 1) * sizeof(char));
    int i;
    int c = 0;
    for(i = 0; i < strlen(command); i++) {
        if(command[i] == '>') {
            redir_args2[c] = '>'; 
            c++;
        }
        if(command[i] == '<') {
            redir_args2[c] = '<';
            c++; 
        }
    }

    redir_args2[tokens] = '\0';

    return redir_args2;
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

    char **args = malloc((tokens + 1) * sizeof(char *));
    int i = 0;
    while(i < tokens)
    {

        args[i] = trim(strsep(&command, " "));
        i++;
    }
    args[tokens] = '\0';
    return args;
}
