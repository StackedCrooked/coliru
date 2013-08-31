#include <iostream>

constexpr unsigned bar(unsigned q) {
    return q;
}

template<unsigned N>
unsigned foo() {
    return N;
}

template<typename F>
void print(F f) {
    std::cout << f() << std::endl;
}

template<unsigned Q>
void stuff() {
    constexpr unsigned n = bar(Q);
    print([]() { return foo<n>(); });
}

int main() {
    stuff<13>();
}