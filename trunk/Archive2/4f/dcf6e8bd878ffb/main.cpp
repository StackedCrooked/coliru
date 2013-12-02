#include <iostream>

struct S {};

template<typename T>
void foo(T t) {
    std::cout << t;
}

template<typename T>
void bar(T t) {
    foo(t);
}

int main() {
    S s;
    bar(s);
}