#include <stdio.h>
#include <time.h>
 
int main(void)
{
    time_t epoch = 0;
    printf("%ld seconds since the epoch began\n", (long)epoch);
    printf("%s", asctime(gmtime(&epoch)));
}