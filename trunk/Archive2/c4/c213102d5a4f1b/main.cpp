#include <stdio.h>
#include <stdint.h>

typedef union {
    float f;
    uint16_t a[2];
} U;

int main()
{
    U u;

    u.f = 3.14f;
    printf("%g -> %#x %#x\n", u.f, u.a[0], u.a[1]);
    return 0;
}