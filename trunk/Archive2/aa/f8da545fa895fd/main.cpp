#include <stdio.h>
#include <stdlib.h>
 
int main(void)
{O
    int ret_code = fputs("Hello World",stdout);
    if ((ret_code == EOF) && (ferror(stdout)))   /* test whether EOF was reached */
    {
       perror("fputs()");
       fprintf(stderr,"fputs() failed in file %s at line # %d\n", __FILE__,__LINE__-4);
       exit(EXIT_FAILURE);
    }
    
    
 
    return EXIT_SUCCESS;
}