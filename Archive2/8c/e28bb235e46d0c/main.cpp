#include <iostream>

int add(int a, int b) {
    return a + b;
}

int add(int a, int b, int c) {
    return a + b + c;
}

template<class Func, class... Args>
auto apply(Func fn, Args... args) {
    return [fn, args...](auto... sargs){ return fn(args..., sargs...); };
}

int main() {
    std::cout << apply(add, 1)(2, 3)   << '\n';
    std::cout << apply(add, 3, 4, 5)() << '\n';
    std::cout << apply(add)(33, 6, 3)  << '\n';
}