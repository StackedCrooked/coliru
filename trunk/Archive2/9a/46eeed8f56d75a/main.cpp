#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

long maximum(long arr[], size_t len)
{
    long res = LONG_MIN;
    
    while (len--)
    {
        if (arr[len] > res)
            res = arr[len];
    }
    return res;
}

int main(void)
{
    const size_t len = 20;
    long arr[len];
    
    srand48((long)time(0));
    
    for (size_t i=0; i<len; ++i)
        printf("%ld\n", arr[i] = (long)lrand48() << 8);
    
    printf("Maximum = %ld\n", maximum(arr, len));
}