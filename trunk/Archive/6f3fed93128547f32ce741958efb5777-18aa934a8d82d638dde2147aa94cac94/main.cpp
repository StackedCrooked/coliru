#include <type_traits>
#include <iostream>
#include <iomanip>

int main() {
    int x[42];
    int* y = x;
    std::cout << std::boolalpha << std::is_same<decltype(x), int*>::value << std::endl;
    std::cout << std::boolalpha << std::is_same<decltype(y), int*>::value << std::endl;
}