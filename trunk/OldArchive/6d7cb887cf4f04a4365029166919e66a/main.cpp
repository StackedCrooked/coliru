#include <type_traits>
#include <iostream>

    template<typename T, T Default>
    struct foo {
        foo(T = Default) { std::cout << "T\n"; }
        foo(int*) { std::cout << "int\n"; }
     };

int main() {
    foo<std::nullptr_t, nullptr> f(nullptr);
}