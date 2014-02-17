#include <iostream>
#include <type_traits>
#include <typeinfo>

template <typename T>
auto F = T{};

int main() {
    int f1 = F<int>; // error: cannot initialize a variable of type 'int' with an lvalue of type 'auto'
    auto f2 = F<int>; // Stacktrace
    decltype(F<int>) f3 = F<int>; // StackFace
    static_assert(std::is_same<int, decltype(F<int>)>::value, "Jabberwocky is killing user.");
    std::cout << typeid(decltype(F<int>)).name(); // Stacktrace
    static_assert(std::is_same<decltype(F<int>), decltype(F<int>)>::value, "Jabberwocky is killing user.");
}
