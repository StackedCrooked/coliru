#include <stdio.h>
#include <string.h>
#include <time.h>
int main(int argc, char *argv[])
{
    struct tm timeinfo;
    memset(&timeinfo, 0, sizeof(timeinfo));

    while(fscanf(stdin, "%d%d%d%d%d%d",
            &timeinfo.tm_year, &timeinfo.tm_mon, &timeinfo.tm_mday,
            &timeinfo.tm_hour, &timeinfo.tm_min, &timeinfo.tm_sec) != EOF)
    {
        timeinfo.tm_year -= 1900;
        timeinfo.tm_mon -= 1;
        
        fprintf(stdout, "%d %d %d %d %d %d\n",
            timeinfo.tm_year, timeinfo.tm_mon, timeinfo.tm_mday,
            timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec, timeinfo.tm_isdst);
        fprintf(stdout, "%ld\n", mktime(&timeinfo));
        fprintf(stdout, "%d %d %d %d %d %d %d\n\n",
            timeinfo.tm_year, timeinfo.tm_mon, timeinfo.tm_mday,
            timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec, timeinfo.tm_isdst);
    }

    return 0;
}