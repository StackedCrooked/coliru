#include <type_traits>
#include <iostream>
#include <iomanip>

int main() {
    int x[42];
    std::cout << std::boolalpha << std::is_same<decltype(x), int*>::value;
}