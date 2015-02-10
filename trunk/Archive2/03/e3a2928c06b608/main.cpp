#include <iostream>
#include <typeinfo>

int main() {
    unsigned int x = 5;
    double y = 10;
    auto z = y/x;
    std::cout << typeid(z).name() << std::endl;
}