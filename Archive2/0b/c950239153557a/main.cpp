#include <stdio.h>

int main(void)
{
    int foo = 42;
    int bar[1] = { foo };
    printf("%d\n", bar[0]);
    return 0;
}
