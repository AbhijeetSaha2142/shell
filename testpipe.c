#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>


int main()
{
    char in[100];
    fgets(in, sizeof(in), stdin);
    printf("%s", in);
}