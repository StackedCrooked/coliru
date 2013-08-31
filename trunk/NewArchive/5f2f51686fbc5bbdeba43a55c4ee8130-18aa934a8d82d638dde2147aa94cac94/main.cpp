#include <type_traits>
#include <iostream>
#include <iomanip>

int main() {
    int x[42];
    std::cout << std::boolalpha << std::is_same<decltype(x), int*>::value << "\n" << std::is_same<decltype(x), int[42]>::value;
}