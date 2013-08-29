#include <iostream>
#include <type_traits>

template <typename T>
void test(T fn) {
    std::cout << std::boolalpha << std::is_same<T, void(*)()>::value << "\n";
}

int main () {
    auto lambda = [] () { int x; x = 2; x *= 3; std::cout << "x"; };
    std::cout << std::boolalpha << std::is_same<decltype(lambda), void(*)()>::value << "\n";
    test(lambda);
}