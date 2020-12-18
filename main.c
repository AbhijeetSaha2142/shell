#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include "parse.h"

int main() 
{
    char cwd[100];
    char line[100];
    while(1)
    {
        if (getcwd(cwd, sizeof(cwd)) != NULL) printf("%s> ", cwd);

        // input 
         // line can only be 100 char
        fgets(line, sizeof(line), stdin); 
        line[strlen(line) - 1] = '\0';

        printf("%s|\n", line); 

        char **commands = parse_commands(line); 
        
        run_commands(commands);

        
    }
}
