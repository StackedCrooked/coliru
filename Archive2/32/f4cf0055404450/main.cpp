#include <iostream>
#include <vector>
#include <type_traits>

int main() {
    auto x = {1, 2, 3};
    std::cout << std::is_same<decltype(x), std::initializer_list<int>>::value;
}