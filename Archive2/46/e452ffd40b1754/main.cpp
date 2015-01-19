#include <iostream>

#define LAM(X, ...) [=](auto&& X) { return __VA_ARGS__; }

int main() {
    auto i = LAM(x, x);
    auto s = LAM(a, LAM(b, LAM(c, ((a)(c))((b)(c)) )));
    
    auto m = (s)(i)(i);
    
    std::cout << (m)(i)(2) << std::endl; // 2
}