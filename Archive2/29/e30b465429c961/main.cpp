#include <iostream>

template<class Lhs, class Rhs>
auto adding_func(const Lhs &lhs, const Rhs &rhs) -> decltype(lhs+rhs) {
    return lhs + rhs;
}

int main() {
    std::cout << adding_func<double,int>(12.7,15);
    asm("");
}