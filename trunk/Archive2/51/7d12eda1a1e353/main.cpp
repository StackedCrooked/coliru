#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#define M1 (-9223372036854775807 - 1)
#define M (-9223372036854775808)
#define B (1 << (sizeof(long long int)*8 - 1))



int main()
{
    long long int a = M1;
    long long int b = B;
    printf("-----    %lld  %lld", a, b);
}