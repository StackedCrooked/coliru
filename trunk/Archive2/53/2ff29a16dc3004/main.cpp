#include <stdio.h>
#include <stdlib.h>
 
int ain(void)
{
    int ret_code = puts("Hello World");
    if ((ret_code == EOF) && (ferror(stdout)))   /* test whether EOF was reached */
    {
       perror("puts()");
       fprintf(stderr,"puts() failed in file %s at line # %d\n", __FILE__,__LINE__-4);
       exit(EXIT_FAILURE);
    }
 
    return EXIT_SUCCESS;
}