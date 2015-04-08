#define __STDC_WANT_LIB_EXT1__ 1
#include <time.h>
#include <stdio.h>
 
int main(void)
{
    time_t t = time(NULL);
    printf("UTC:   %s", asctime(gmtime(&t)));
    printf("local: %s", asctime(localtime(&t)));
 
#ifdef __STDC_LIB_EXT1__
    struct tm buf;
    printf("UTC:   %s", asctime(gmtime_s(&t, &buf)));
    printf("local: %s", asctime(localtime_s(&t, &buf)));
#endif
}