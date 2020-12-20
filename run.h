#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int len_arr(char **);
void run(char **);
void run_pipes(char **);
void run_commands(char **);