#include <stdio.h>
#include <limits.h>

void print_bits(unsigned int x)
{
    const unsigned int n = sizeof(x) * CHAR_BIT;
    unsigned int mask = 1 << (n - 1);
    char s[n + 1];

    for (unsigned int i = 0; i < n; ++i)
    {
        s[i] = (x & mask) ? '1' : '0';
        mask >>= 1;
    }
    s[n] = '\0';
    puts(s);
}

int main()
{
    for (unsigned int i = 0; i < 256; ++i)
    {
        print_bits(i);
    }
    return 0;
}
