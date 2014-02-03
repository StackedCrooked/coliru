#include <iostream>
#include <type_traits>

int main() {
    auto x = []{};
    auto y = []{};
    std::cout << std::is_same<decltype(x), decltype(y)>::value;
}