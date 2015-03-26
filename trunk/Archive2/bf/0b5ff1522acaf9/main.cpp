#include <iostream>
#include <typeinfo>

int main() {
    std::cout << typeid((unsigned char)1 * 1).name() << " " << typeid(int).name();
}