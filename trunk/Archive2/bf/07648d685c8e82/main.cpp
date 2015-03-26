#include <iostream>
#include <typeinfo>

int main() {
    std::cout << typeid(1U * 1LL).name() << " " << typeid(1LL).name();
}