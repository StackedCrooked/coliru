#include <stdio.h>
#include <stdlib.h>
 
int main(void)
{
    FILE* tmpf = tmpfile();
    fputs("Alan Turing\n", tmpf);
    fputs("John von Neumann\n", tmpf);
    fputs("Alonzo Church\n", tmpf);
 
    rewind(tmpf);
 
    char buf[8];
    while (fgets(buf, sizeof buf, tmpf) != NULL)
          printf("\"%s\"\n", buf);
 
    /* Test reason for reaching NULL. */
    if (feof(tmpf))          /* if failure caused by end-of-file condition */
       puts("End of file reached");
    else if (ferror(tmpf))   /* if failure caused by some other error      */
         {
            perror("fgets()");
            fprintf(stderr,"fgets() failed in file %s at line # %d\n", __FILE__,__LINE__-9);
            exit(EXIT_FAILURE);
         }
 
    return EXIT_SUCCESS;
}