#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include "parse.h"

// order: commands > redir > pipes > args

//length array
int len_arr(char **input)
{
    int i = 0;
    while(input[i]) i++;
    return i; 
}

void run(char **args) 
{
    // change directory
    if (strcmp(args[0], "cd") == 0) {
        int k = chdir(args[1]);
        if (k == -1) {
            printf("errno: %d\terror: %s\n", errno, strerror(errno));
        }
    }
    // exit
    else if (strcmp(args[0], "exit") == 0) {
        kill(getpid(), SIGKILL);
    }
    else {
        //arg[0] is program, everything else arguments
        int f = fork();

        if (!f) {// child
            int k = execvp(args[0], args);
            if (k == -1) {
                printf("errno: %d\terror: %s\n", errno, strerror(errno));
            }
        } 
        
        if (f) //parent 
        {
            int status;
            int pid = wait(&status); 
        }
    }
    
}

void run_pipes(char **pipe_args) { //can only run 2 argument pipes
    if (len_arr(pipe_args)== 1) 
    {
        run(parse_args(pipe_args[0]));
    }
    else 
    {
        int fds[2];
        pipe(fds);
        int f = fork();
        if (!f) {
            close(fds[0]); 
            int backup_sdout = dup( STDOUT_FILENO );
            dup2(fds[1], STDOUT_FILENO); 
            run(parse_args(pipe_args[0]));
            dup2(backup_sdout, STDOUT_FILENO); 
            kill(getpid(), SIGKILL);            
        }
        if (f) {
            int status; 
            int pid = wait(&status);

            close(fds[1]);
            int backup_sdin = dup( STDIN_FILENO ); 
            dup2(fds[0], STDIN_FILENO); 
            run(parse_args(pipe_args[1]));
            dup2(backup_sdin, STDIN_FILENO); 
        }
    }
}

// note that < exclusively redirects to input, > redirects to output
void run_redirs(char **commands)
{
    if (len_arr(commands) == 1)
    {
        run_pipes(parse_pipes(commands[0])); 
    }
    else {
        
    }
}

void run_commands(char **commands) 
{
    int i = 0;
    while(commands[i]) {
        run_redirs(parse_redirs(commands[i]));
        printf("\n");
        i++;
    }
}

