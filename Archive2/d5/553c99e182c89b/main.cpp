#include <cstdio>

void foo(int const &) {
    std::puts("Hello, World!\n");   
}

int main() {
    void foo(int const &);

    foo(1); // const lvalue reference can bind to rvalue

    int a;
    foo(a); // and lvalue
}
