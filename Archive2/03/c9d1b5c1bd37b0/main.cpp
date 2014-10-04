#include <cinttypes>
#include <stdint.h>
#include <stdio.h>

int main() {
    uintptr_t i = 0;
    i--;
    printf("%" PRIuPTR "\n", i);
    return 0;
}
