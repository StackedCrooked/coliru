#include <iostream>

template<typename ...T>
void f(void(*ptr)(T...)) {
    ptr(1);
}

void g(int) { std::cout << "g(int)"; }
void g(int, int) { std::cout << "g(int, int)"; }

int main() {
    f(g);
}