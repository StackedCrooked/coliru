#include <iostream>

template<int N>
struct Foo {
    void operator()() {
        std::cout << N << '\n';
    }
};

int main() {
    Foo<10 / 0> foo;
    foo();
}
