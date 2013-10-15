#include <stdio.h>
#include <time.h>
 
int main()
{
    time_t now;
    time(&now);
 
    struct tm beg;
    beg = *localtime(&now);
 
    // set beg to the beginning of the month
    beg.tm_hour = 0;
    beg.tm_min = 0;
    beg.tm_sec = 0;
    beg.tm_mday = 0;
 
    int day = (difftime(now, mktime(&beg))/86400);
 
    printf("%d days have passed since the beginning of the month.\n", day);
 
    return 0;
}