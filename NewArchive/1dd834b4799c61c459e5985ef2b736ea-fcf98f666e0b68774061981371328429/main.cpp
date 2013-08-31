#include <iostream>
#include <type_traits>

template<class T /*, class U = typename std::remove_reference<T>::type */>
struct A {
    T t; // U t
    A(T&& t): t(std::forward<T>(t)) {}
    A& modify() {
        t += 100;
        return *this;
    }
    T ret() {
        return t;
    }
};

template<typename T>
A<T> make(T&& t) {
    return { std::forward<T>(t) };
}

int main() {
    int a = 10;
    int b = make(a).modify().ret();
    std::cout << a << '\n' << b;
}