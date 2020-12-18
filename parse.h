#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>

char **parse_args(char *);
char **parse_commands(char *);
void run_commands(char **);