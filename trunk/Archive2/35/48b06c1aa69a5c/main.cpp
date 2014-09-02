#include <stdio.h>
#include <stdlib.h>
 
int main(void)
{
    FILE* tmpf = tmpfile();
    fputs("abcde\n", tmpf);
 
    rewind(tmpf);
 
    int ch;
    while ((ch=fgetc(tmpf)) != EOF)   /* read/print characters including newline */
          printf("%c", ch);
 
    /* Test reason for reaching EOF. */
    if (feof(tmpf))          /* if failure caused by end-of-file condition */
       puts("End of file reached");
    else if (ferror(tmpf))   /* if failure caused by some other error      */
         {
            perror("fgetc()");
            fprintf(stderr,"fgetc() failed in file %s at line # %d\n", __FILE__,__LINE__-9);
            exit(EXIT_FAILURE);
         }
 
    return EXIT_SUCCESS;
}