#include <stdio.h>

void a() {}
void b() {}

int main() {
    printf("%d %p %p\n", a == b, (void*)a, (void*)b);
    auto x = a;
    auto y = b;
    printf("%d %p %p\n", x == y, (void*)x, (void*)y);
}
