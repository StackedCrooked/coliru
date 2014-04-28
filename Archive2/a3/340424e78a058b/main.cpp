#include <stdlib.h>
#include <stdio.h>
 
int main(void)
{
    printf("TMP_MAX  = %d\n", TMP_MAX);
    printf("L_tmpnam = %d\n", L_tmpnam);
    char buffer[L_tmpnam] = {'\0'};
    char * fname = tmpnam(buffer);
    printf("%p %p\n", fname,buffer);
    if (fname == NULL)
    {
      fprintf(stderr,"tmpnam() failed in file %s at line # %d\n", __FILE__,__LINE__-3);
      perror("tmpnam()");
      exit(EXIT_FAILURE);
    }
    printf("%s\n", fname);
    printf("%s\n", buffer);
 
    exit(EXIT_SUCCESS);
}