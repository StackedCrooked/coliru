
#include <stdio.h>
#include <time.h>
void logMine(char *szDebugString)
{
    printf("%s", szDebugString); //only for debug

    time_t currentTime;

    time(&currentTime);

    printf("%s", szDebugString); //only for debug
    printf("[%d] %s\n", currentTime, szDebugString);
}

int main () {
    
        return 0;
}
