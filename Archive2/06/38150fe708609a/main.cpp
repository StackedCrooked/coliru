#include "/Archive2/78/7b45acd2e10386/main.cpp" // runtime `get`, `get_variant_t`

#include <iostream>
#include <vector>
#include <type_traits>

int main() {
    auto x = {1, 2, 3};
    std::cout << std::is_same<decltype(x), std::initializer_list<int>>::value;
}