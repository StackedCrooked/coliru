#include <stdint.h>
#include <stdio.h>

struct Foo
{
    uint8_t a;
    uint32_t b;
} __attribute__((packed));


int main()
{
    printf("sizeof(Foo): %zu", sizeof(struct Foo));
}