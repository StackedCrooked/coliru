#include <stdio.h>
#include <time.h>
#include <stdlib.h>
 
int main(void)
{
    time_t result = time(NULL);
    if (result == ((time_t)-1))
    {
       fprintf(stderr,"time() failed in file %s at line # %d\n", __FILE__,__LINE__-3);
       exit(EXIT_FAILURE);
    }
 
    printf("%s", asctime(localtime(&result)));
    printf("%d seconds since the Epoch", (int)result);
    return EXIT_SUCCESS;
}