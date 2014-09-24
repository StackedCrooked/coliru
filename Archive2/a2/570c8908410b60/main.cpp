#include <stdio.h>
#include <stdint.h>
#include <string.h>

int main()
{
    float f = 3.14f;
    uint16_t a[2];
    memcpy(a, &f, sizeof(a));
    printf("%g -> %#x %#x\n", f, a[0], a[1]);
    return 0;
}