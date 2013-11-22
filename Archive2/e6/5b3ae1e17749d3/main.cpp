#include <stdio.h>
#include <time.h>
 
int main()
{
    time_t t = time(NULL);
    printf("UTC:   %s", asctime(gmtime(&t)));
    printf("local: %s", asctime(localtime(&t)));
 
    return 0;
}