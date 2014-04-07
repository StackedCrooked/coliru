#include <iostream>
#include <typeinfo>

int main() {
    auto x = 1;
    std::cout << (typeid(decltype(x)) == typeid(int));
}