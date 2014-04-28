#include <iostream>

template<typename LHS, typename RHS>
auto compose_two(LHS lhs, RHS rhs) {
    return [=](auto x) { return lhs(rhs(x)); };
}

template<typename... Args>
struct compose_impl;

template<typename LHS, typename... Args>
struct compose_impl<LHS, Args...> {
    static auto run(LHS lhs, Args... args) {
        return compose_two(lhs, compose_impl<Args...>::run(args...));
    }
};

template<typename LHS, typename RHS>
struct compose_impl<LHS, RHS> {
    static auto run(LHS lhs, RHS rhs) {
        return compose_two(lhs, rhs);
    }
};

template<typename... Args>
auto compose(Args... args) {
    return compose_impl<Args...>::run(args...);
}

int inc(int x) { return x + 1; }

int main() {
    int y = 5;
    auto f = compose(inc, [=](int x) { return y*x; }, inc, inc);
    std::cout << f(8);
}
