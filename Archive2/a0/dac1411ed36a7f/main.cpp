#include <stdio.h>

int f();

void g() {
    puts("g");
}

int a = f();

int x = (g(), 22);

int f() {
    puts("f");
    ++x;
    return 5;
}

int main() {
    printf("%d\n", x);
}