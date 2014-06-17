// see here for the example: http://en.wikipedia.org/wiki/Strategy_pattern#Example
#include <type_traits>
#include <iostream>

template<typename Function>
int strategy(Function f, int a, int b) {
    static_assert(std::is_convertible<decltype(f(a, b)), int>::value, "Must return int");
    return f(a, b);
}

int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int multiply(int a, int b) {
    return a * b;
}

int main() {
    std::cout << "Result A: " << strategy(add, 3, 4) << '\n'
              << "Result B: " << strategy(subtract, 3, 4) << '\n'
              << "Result C: " << strategy(multiply, 3, 4) << '\n';
}