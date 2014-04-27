#include <iostream>

auto id = [](auto x) { return x; };

template <typename RHS>
auto operator>>(decltype(id), RHS rhs) {
    return [=](auto x) { return rhs(x); };
}

template <typename LHS, typename RHS>
auto operator>>(LHS lhs, RHS rhs) {
    return [=](auto x) { return lhs(rhs(x)); };
}

int inc(int x) { return x + 1; }

int main() {
    int y = 5;
    auto f = inc >> [=](int x) { return y*x; } >> inc >> inc;
    std::cout << f(8);
}
