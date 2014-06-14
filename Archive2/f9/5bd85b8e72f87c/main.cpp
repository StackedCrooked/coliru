#include <stdio.h>

void print(int a, int b, int c) {
    printf("%i %i %i\n", a, b, c);
    printf("%i %i %i\n", c, b, a);
}

int main() {
    int a, b, c;
    printf("Enter three digits: ");
    scanf("%i %i %i", &a, &b, &c);
    print(a, b, c);
}
