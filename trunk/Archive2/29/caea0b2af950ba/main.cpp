#include <stdio.h>
#include <time.h>
 
int main()
{
    time_t result = time(NULL);
    printf("%s", asctime(localtime(&result)));
    printf("%d seconds since the Epoch", (int)result);
}