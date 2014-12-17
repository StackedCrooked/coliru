#include <stdio.h>
#include <stdlib.h>
 
int main(void)
{
    FILE *fp = fopen("data.txt","w");
    if (fp == NULL)
    {
       perror("fopen()");
       fprintf(stderr,"fopen() failed in file %s at line # %d\n", __FILE__,__LINE__-4);
       return EXIT_FAILURE;
    }
 
    /* Normal processing continues here. */
 
    fclose(fp);
    return EXIT_SUCCESS;
}