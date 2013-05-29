#include <cstdio>

int main()
{
    volatile int a = 1;
    volatile int b = 0;
    volatile int c = a/(b+.00000001);
    return c;
}