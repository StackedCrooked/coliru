#include <cstdio>

void foo(int const &c) {
    std::puts("Hello, World!\n");   
}

int main() {
    void foo(int const &);

    foo(1); // the const lvalue reference parameter is bound to
            // the rvalue resulting from the expression '1'

}
