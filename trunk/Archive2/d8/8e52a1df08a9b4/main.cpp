#include <iostream>
#include <typeinfo>

int main() {
    std::cout << typeid(0x9e3779b9).name() << ", size " << sizeof(0x9e3779b9) << "\n";
    std::cout << typeid(2654435769).name() << ", size " << sizeof(2654435769) << "\n";
}
