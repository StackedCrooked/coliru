#include <iostream>

int foo() {
    static int i;
    return i++;
}

int main() {
    std::cout << foo() << foo() << '\n';
}