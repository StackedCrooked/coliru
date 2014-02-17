#include <iostream>
#include <type_traits>
#include <typeinfo>

template <typename T>
auto F = T{};

int main() {
    int f1 = F<int>; // error: cannot initialize a variable of type 'int' with an lvalue of type 'auto'
    auto f2 = F<int>; // Stacktrace
    decltype(F<int>) f3 = F<int>; // StackFace
    std::cout << std::is_same<int, decltype(F<int>)>::value; // false
    std::cout << typeid(decltype(F<int>)).name(); // Stacktrace
    std::cout << std::is_same<decltype(F<int>), decltype(F<int>)>::value; // true
}
