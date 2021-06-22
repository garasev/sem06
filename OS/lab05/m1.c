#include <stdio.h>
#include <fcntl.h>
#define FILENAME "alphabet.txt"


int main()
{
    int fd = open(FILENAME, O_RDONLY);
    if (fd == -1)
    {
        printf("Error opening fd %s\n", FILENAME);
        return -1;
    }
    printf("fd: %d\n", fd);
    
    FILE *fs1 = fdopen(fd, "r");
    char buff1[20];
    setvbuf(fs1, buff1, _IOFBF, 20);

    FILE *fs2 = fdopen(fd, "r");
    char buff2[20];
    setvbuf(fs2, buff2, _IOFBF, 20);

    int flag1 = 1, flag2 = 2;
    while(flag1 == 1 || flag2 == 1)
    {
        char c;
        flag1 = fscanf(fs1,"%c", &c);
        if (flag1 == 1) {
           // fprintf(stdout,"fs1:%c  ", c);
           fprintf(stdout,"%c", c);
        }
        flag2 = fscanf(fs2,"%c", &c);
        if (flag2 == 1) {
            fprintf(stdout,"%c", c);
            //fprintf(stdout,"fs2:%c", c);
        }
        //fprintf(stdout,"\nbuf1: %s\nbuf2: %s\n", buff1, buff2);
    }
    fprintf(stdout,"\n");
    fprintf(stdout,"buf1: %s\nbuf2: %s\n", buff1, buff2);
    return 0;
}