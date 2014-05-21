#include <stdio.h>
#include <inttypes.h>

uint8_t foo(uint8_t bar)
{
    return bar + bar;
}

int main(void)
{
    printf("%" PRId8 "\n", foo(0xff-1));
    return 0;
}