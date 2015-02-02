#include <cstdio>

void foo(int const &&) {
    std::puts("Hello, World!\n");   
}

int main() {
    void foo(int const &&);

    int a;

    foo(a); // error, the expression 'a' is an lvalue; rvalue references cannot bind to lvalues
}
