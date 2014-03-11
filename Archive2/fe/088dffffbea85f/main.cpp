#include <iostream>
#include <type_traits>

struct S1 {
    void method() {}
};

struct S2 {};

template<typename T>
void foo(T t) {
    fooImpl(t, 0);
}

template<typename T>
auto fooImpl(T t, int) -> decltype(t.method(), void()) {
    std::cout << "T has method()\n";
}

template<typename T>
void fooImpl(T, long) {
    std::cout << "T does not have method()\n";
}

int main() {
    foo(S1{});
    foo(S2{});
}