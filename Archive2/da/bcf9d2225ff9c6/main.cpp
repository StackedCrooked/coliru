#include <stdio.h>
#include <stdint.h>

uint64_t factorial(uint64_t n) {
    uint64_t i = 2;
    uint64_t v = 1;
    for (; i <= n; i++) {
        v *= i;
    }

    return v;
}

int main() {
    uint64_t i = 1;
    for (; i < 24; i++) {
        printf("%-4u: %lu\n", i, factorial(i));
    }

    return 0;
}