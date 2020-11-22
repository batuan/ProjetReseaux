#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
 
int main(int argc, char **argv)
{
    printf("argument count: %s\n", argv[3]);
    int filedesc = open("./testfile.txt", O_WRONLY | O_APPEND);
    printf("file desc: %d", filedesc);
    if(filedesc < 0)
        return 1;
 
    if(write(filedesc,"This will be output to testfile.txt\n", 36) != 36)
    {
        write(2,"There was an error writing to testfile.txt\n", 36);    // strictly not an error, it is allowable for fewer characters than requested to be written.
        return 1;
    }
    close(filedesc);
    return 0;
}