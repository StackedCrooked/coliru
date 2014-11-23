#include <stdio.h>
#include <time.h>
 
int main(void)
{
    time_t epoch = 0;
    printf("%d seconds since the epoch began\n", (int)epoch);
    printf("%s\n", asctime(localtime(&epoch)));
 
    return 0;
}
