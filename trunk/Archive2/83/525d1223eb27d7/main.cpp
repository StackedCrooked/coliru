#include <iostream>

struct X {
    template<class T> X(T, T){ std::cout << "1\n"; }
    template<class T> X(std::initializer_list<T>){ std::cout << "2\n"; }
};

int main() {
    int x = 0;
    X{x, x};
    X{&x, &x};
}
