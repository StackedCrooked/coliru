#include <typeinfo>
#include <iostream>

int main() {
    std::cout << typeid(1 - 1).name() << '\n';
    std::cout << typeid(1u - 1u).name() << '\n';
    return 0;
}
