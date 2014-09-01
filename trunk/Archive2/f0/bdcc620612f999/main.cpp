#include <stdio.h>

void print_stars(unsigned x)
{
    while (x)
    {
        putchar((x & 1) ? '*' : ' ');
        x >>= 1;
    }
    putchar('\n');
}

int main()
{
    unsigned x = 1;
    do
    {
        print_stars(x);
        x ^= (x << 1);
    } while (x != 1);
}
