#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>

int count_tokens(char *, char);
char **parse_args(char *);
char **parse_pipes(char *);
char **parse_redirs(char *);
char **parse_commands(char *);
