#include <iostream>
#include <typeinfo>

int main() {
    auto x = []{ return 123; };
    std::cout << typeid(x).name();
}