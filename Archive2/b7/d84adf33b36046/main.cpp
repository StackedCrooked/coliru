#include <iostream>

static void f();
static int i = 0; // #1
void g() {
    extern void f(); // internal linkage
    int i; // #2 i has no linkage
    {
        extern void f(); // internal linkage
        extern int i; // #3 external linkage
        i = 5;
    }
}

int main() {
    std::cout << i << std::endl;
    g();
    std::cout << i << std::endl;
}