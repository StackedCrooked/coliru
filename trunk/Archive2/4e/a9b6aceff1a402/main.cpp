#include <stdio.h>
#include <time.h>
#include <stdlib.h>
 
int main(void)
{
    time_t t = time(NULL);
    struct tm *tmptr = gmtime(&t);
    if (tmptr == NULL)
    {
       fprintf(stderr,"gmtime() failed in file %s at line # %d\n", __FILE__,__LINE__-3);
       exit(EXIT_FAILURE);
    }
 
    printf("UTC:   %s", asctime(tmptr));
    printf("local: %s", asctime(localtime(&t)));
 
    return EXIT_SUCCESS;
}