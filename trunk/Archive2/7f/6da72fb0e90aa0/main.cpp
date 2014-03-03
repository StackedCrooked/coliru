#include <stdio.h>
#include <time.h>
#include <stdlib.h>
 
int main()
{
    time_t result = time(NULL);
    time_t new_0 = time(NULL);
    int c = 0;
    while(c<3)
    {
        new_0 = time(NULL);
        if(new_0 > result)
        {
            printf("%d\n", (int)(new_0));
            result = new_0;
            c++;
        }
    }
}