#include <stdio.h>

int main(void)
{
    unsigned char a  = 15; /* one byte */
    unsigned short b = 15; /* two bytes */
    unsigned int c   = 15; /* four bytes */

    long x = -a; /* eight bytes */
    printf("%ld\n", x);

    x = -b;
    printf("%ld\n", x);

    int z= -c;
    printf("%ld\n", x);

    return 0;
}