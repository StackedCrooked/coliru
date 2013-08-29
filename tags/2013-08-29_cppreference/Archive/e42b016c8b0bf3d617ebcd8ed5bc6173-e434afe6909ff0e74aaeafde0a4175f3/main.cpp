#include <iostream>
#include <functional>

void foo(int) {
    std::cout << "foo(int)\n";
}

void foo(int&) {
    std::cout << "foo(int&)\n";
}

int main() {
    int i;
    foo(5);
    static_cast<void(*)(int)>(foo)(i);
    static_cast<void(*)(int&)>(foo)(i);
}
