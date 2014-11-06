#include <iostream>

template<typename T>
void f(T&&) {
    std::cout << __PRETTY_FUNCTION__ << '\n';
}

int g() { return 20; }

int main() {
    int x = 10;
    int&& y = 20;
    int& z = x;
    const int a = 10;
    const int& b = a;
    f(10);
    f(x);
    f(y);
    f(z);
    f(g());
    f(a);
    f(b);
}