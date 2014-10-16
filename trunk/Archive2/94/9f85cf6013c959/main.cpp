#include <iostream>
#include <tuple>
#include <type_traits>


int main() {
    std::cout << std::is_empty<std::tuple<>>::value;
}