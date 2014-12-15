#include <stdio.h>
#include <time.h>
 
int main(void)
{
    printf("%s\n", asctime(&(struct tm){.tm_mday=7
    }));
}