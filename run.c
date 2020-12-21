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
#include <fcntl.h>

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
            printf("in run: errno: %d\terror: %s\n", errno, strerror(errno));
        }
    }
    // exit
    else if (strcmp(args[0], "exit") == 0) {
        kill(getpid(), SIGKILL);
    }

    else if (strcmp(args[0], "rm") == 0) {
        int k = remove(args[1]);
        if (k == -1) {
            printf("errno: %d\terror: %s\n", errno, strerror(errno));
        }
    }
    
    else {
        //arg[0] is program, everything else arguments
        int f = fork();
        if (!f) {// child
            int k = execvp(args[0], args);
            if (k == -1) {
                printf("in run: errno: %d\terror: %s\n", errno, strerror(errno));
            }
            kill(getpid(), SIGKILL);
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
void run_redirs(char **commands, char *args)
{
    if (len_arr(commands) == 1)
    {
        run_pipes(parse_pipes(commands[0]));
    }
    else {
        int i = 0;
        int fdsin;
        int fdsout;
        int backup_sdin;
        int backup_sdout;
        int f = fork(); 

        
        if(!f) {
            
            while(args[i]) {
            
                if(args[i] == '>'){
                    fdsout = open(trim(commands[i+1]), O_WRONLY | O_CREAT | O_TRUNC, 0644);
                    if (fdsout == -1) {
                        printf("in run_redirs: errno: %d\terror: %s\n", errno, strerror(errno));
                    }
                    backup_sdout = dup( STDOUT_FILENO );
                    //redirects fdsout to stdout
                    dup2(fdsout, STDOUT_FILENO);

                }
                if(args[i] == '<'){
                    fdsin = open(trim(commands[i+1]), O_RDONLY);
                    if (fdsin == -1) {
                        printf("in run_redirs: errno: %d\terror: %s\n", errno, strerror(errno));
                    }
                    
                    backup_sdin = dup( STDIN_FILENO );
                    //redirects stdin to fdsin
                    dup2(fdsin, STDIN_FILENO);
                    printf("reached\n");
                }
                i++;
            }
            run_pipes(parse_pipes(commands[0]));

            //closes
            if (!fdsin) {
                dup2(backup_sdin, STDIN_FILENO);
                close(fdsin);
            }
            if (!fdsout) {
                dup2(backup_sdout, STDOUT_FILENO);
                close(fdsout);
            }
            kill(getpid(), SIGKILL);
        }
        if (f)
        {
            int status;
            int pid = wait(&status);
        }
        
        
    }
}

void run_commands(char **commands)
{
    int i = 0;
    while(commands[i]) {
        run_redirs(parse_redirs(commands[i]), parse_redirs2(commands[i]));
        i++;
    }
}

