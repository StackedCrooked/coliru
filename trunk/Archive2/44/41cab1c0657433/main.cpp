#include <iostream>
#include <typeinfo>

int main() {
    std::cout << typeid(0x9e3779b9).name() << "\n";
    std::cout << typeid(2654435769).name() << "\n";
}
