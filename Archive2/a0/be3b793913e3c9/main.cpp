#include <iostream>
#include <typeinfo>

int main() {
    std::cout << typeid((unsigned)1 * 1LL).name() << " " << typeid(1LL).name();
}