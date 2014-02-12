#include <utility>

struct lambda1 {
    template<typename F>
    auto operator() (F &&f) const;
};

template<typename F>
struct lambda2 {
    lambda1 const &l1;
    F &&f;
    lambda2(lambda1 const &l1, F &&f) : l1(l1), f(std::forward<F>(f)) {}

    template<typename X>
    auto operator() (X x) const { return f( l1(f))(x); }
}; 

template<typename F>
auto lambda1::operator() (F &&f) const {
    return lambda2<F>(*this, std::forward<F>(f));
}   //                  ^
    //                  |
    //                  --- there's no syntax to do this inside a lambda.
#include <iostream>

int main() {
  lambda1 fix;
  std::cout << fix( [](auto&&){return [](int x){return x;};} )(5) << "\n";
}