#include <iostream>
#include <type_traits>

int func(int, int) {
    std::cout << "Function!\n";
    return 1;
}

int main() {
    typename std::result_of<decltype(func)&(int, int)>::type val = 1;
    std::cout << val;
    return 0;
}