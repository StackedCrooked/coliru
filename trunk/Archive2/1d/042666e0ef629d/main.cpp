#include <iostream>
#include <tuple>
#include <type_traits>


int main() {
    std::cout << std::boolalpha << std::is_empty<std::tuple<>>::value << std::endl;
}