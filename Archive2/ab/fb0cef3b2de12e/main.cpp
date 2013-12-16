#include <iostream>

void foo() noexcept(false) {}

int main() {
    std::cout << noexcept(foo);
}
