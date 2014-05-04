#include <iostream>

void *p;

int main() {
    void *p = &p;
    std::cout << &p << '\n' << &::p << '\n' << p;
}