#include <iostream>

int bar() { return 123; }

const int foo = bar();

int main() {
    std::cout << foo;
}