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

char **parse_args(char *command) 
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
    printf("spaces: %d\n", spaces);
    // subtracts spaces at beginning and end
    if (command[0] == ' '){
        spaces--;
    }
    if (command[i - 1] ==  ' '){
        spaces--;
    }

    char **args = malloc((spaces + 1) * sizeof(char *));
    i = 0;
    while(args[i] = strsep(&command, " ")) i++;
    return args;
}

void run(char **args) 
{
    //arg[0] is program, everything else arguments
    int f = fork();

    f = fork();

    if (!f) {// child
        execvp(args[0], args);
    } 
    
    if (f) //parent 
    {
        int status;
        int pid = wait(&status);
    }
}

void print_string_array(char **input) {
    int i = 0;
    while(input[i]) {
        printf("%s\n", input[i]); 
        i++;
    }
    printf("\n");
}

int main()
{
    char test[] = "ls -a -l ; ls -l";
    char **test_commands = parse_commands(test);
    printf("commands: \n");
    print_string_array(test_commands);
    char test2[] = "ls -a -l";
    printf("args for ls -a -l:  \n");
    char **test_args = parse_args(test2); 
    
    print_string_array(test_args);
    run(test_args);


}





