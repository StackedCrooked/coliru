#include <stdio.h>

int main() {
    int x = 42;
    
    printf("%f\n", (float)x);
    printf("%f\n", *(float*)&x);
};
