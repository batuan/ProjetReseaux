#include <stdio.h>
#include <string.h>

int main ()
{
    char command[50];
    int error = 0;
    sprintf(command, "sh ../test.sh %s", "abc");
    error = system(command);
    printf("my command %s\n", command);
    printf("error: %d\n", error);
    return(0);
} 