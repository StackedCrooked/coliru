#include <stdio.h>
#include <time.h>
#include <stdlib.h>
 
int main(void)
{
    time_t t = time(NULL);
    printf("UTC:   %s", asctime(gmtime(&t)));
    struct tm *tmptr = localtime(&t);
    if (tmptr == NULL)
    {
       fprintf(stderr,"localtime() failed in file %s at line # %d\n", __FILE__,__LINE__-3);
       exit(EXIT_FAILURE);
    }
    printf("local: %2d", tmptr->tm_mday);
 
    return EXIT_SUCCESS;
}