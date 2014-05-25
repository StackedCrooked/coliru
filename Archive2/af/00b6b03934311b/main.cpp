#include <iostream>

int add(int a, int b, int c) {
    return a + b + c;
}

template<class Func, class... Args>
auto curry(Func fn, Args... args) {
    return [fn, args...](auto... sargs){ return fn(args..., sargs...); };
}

int main() {
    std::cout << curry(add, 1)(2, 3);
}