#include <stdio.h>
#include <inttypes.h>

uint8_t foo(uint8_t bar)
{
    return bar + 134125154523;
}

int main(void)
{
    printf("%" PRId8 "\n", foo(100));
    return 0;
}