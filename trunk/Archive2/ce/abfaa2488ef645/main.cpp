#include <stdio.h>

void g(void) { printf("%d", 10); }
void f(void(*g)(void)) { g(); g(); }

int main() {
    f(&g);
    return 0;
}
