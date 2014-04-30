#include <utility>
#include <iostream>

#define LIFT(f) [](auto&&... as) -> decltype(auto){ return (f)(std::forward<decltype(as)>(as)...); }

template<typename T>
void func(T x) {
    std::cout << x;
}

int main() {
    auto x = LIFT(func);
    x(1);
}