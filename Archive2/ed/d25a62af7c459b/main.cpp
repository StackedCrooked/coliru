#include <stdbool.h>
#include <stdio.h>

int main(void)
{
    bool b = false;

    printf("%u\n", b);

    b = 5 > 3;
    printf("%u\n", b);

    b = 0;
    printf("%u\n", b);

    b = -987;
    printf("%u\n", b);
}