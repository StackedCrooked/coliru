#include <stdio.h>
#include <stdlib.h>

int main(void) {
    printf("%p\n", malloc(10000000));
    return 0;
}
