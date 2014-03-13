#include <stdio.h>

int g1(void) { return 1; }
int g2(void) { return 20; }
int f(int(*g)(void)) { return g(); }

int main() {
    return f(&g1) + f(&g2);
}
