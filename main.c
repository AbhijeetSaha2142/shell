#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() 
{
    char cwd[100];
    while(1)
    {
        if (getcwd(cwd, sizeof(cwd)) != NULL) printf("%s>", cwd)
        
    }
}
