#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>

char **parse_commands(char *line) 
{
    char **commands = malloc(6 * sizeof(char *));
    int i = 0;
    while(commands[i] = strsep(&line, ";")) i++;
    return commands;
}

char **parse_args(char *command) 
{
    // counts spaces
    int spaces = 0;
    int i;
    for (i = 0; command[i]; ++i)
    {
        if (command[i] == " "){
            ++spaces;
        }
    }

    // subtracts spaces at beginning and end
    if (command[0] == " "){
        spaces--;
    }
    if (command[i - 1] == " "){
        spaces--;
    }

    char **args = malloc((spaces + 1) * sizeof(char *));
    int i = 0;
    while(args[i] = strsep(&command, " ")) i++;
    return args;
}

void run(char **args) 
{
 //   char line[] = "ls -a -l";
  //  char **args = parse_args(line);
    execvp(args[0],args);
    return 0;
}







