#include <iostream>

template<typename T>
struct Base;

template<>
struct Base<int> {
    void foo() {std::cout << "Base<int>\n";}
};

template<>
struct Base<char> {
    void bar() {std::cout << "Base<char>\n";}
};

template<typename... Ts>
struct S : Base<Ts>... {};

int main() {
    S<int, char> s;
    s.foo();
    s.bar();
}