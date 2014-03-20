#include <iostream>

template<typename ...T, typename F>
void f(void(*ptr)(F, T...)) {
    ptr(1);
}

void g() { std::cout << "g()"; }
void g(int) { std::cout << "g(int)"; }

int main() {
    f(g);
}