#include <iostream>
#include <type_traits>

void func(int) {}

int main() {
    std::cout << std::is_same<decltype(func), void(int)>::value;
}
