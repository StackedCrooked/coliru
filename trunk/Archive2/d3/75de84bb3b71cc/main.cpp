#include <iostream>
#include <type_traits>

int func(int, int) {
    std::cout << "Function!\n";
    return 1;
}

int main() {
    typedef std::result_of<decltype(func)&(int, int)>::type val;
    std::cout << std::boolalpha << "Types are same: " << std::is_same<int, val>::value << std::endl;
    return 0;
}