#include <iostream>

constexpr int add_ce(const int a, const int b) { return a + b; }
int add(const int a, const int b) { return add_ce(a, b); }
// constexpr int add(constexpr int a, constexpr int b) { return add_ce(a, b); } // doesn't compile - can't overload on constexpr-ness of arguments

int main() {
    static_assert(add_ce(1, 2) == 3, "");
    // static_assert(add(1, 2) == 3, ""); // compiler error - add is not constexpr
    constexpr int a = 1, b = 2;
    static_assert(add_ce(a, b) == 3, ""); // fine - add_ce(a, b) is constepxr
    int c = 2;
    // static_assert(add_ce(a, c) == 3, ""); // compiler error - c is not constexpr so add_ce(a, c) is not constexpr
    std::cout << add_ce(a, c) << std::endl; // fine - can call a constexpr function with non const arguments in a non constexpr context
}
