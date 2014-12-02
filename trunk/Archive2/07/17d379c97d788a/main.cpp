#include <stdio.h>

int TimesFive(const int i) {
    int n = i;
    asm("leal (%0,%0,4),%0"
         : "=r" (n)
         : "0" (n));
    return n;
}

int main() {
    printf("Answer: %i", TimesFive(9));
}