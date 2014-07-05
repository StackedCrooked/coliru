#include <iostream>

struct S {
    S(int x) : b_{x}, a_{2 * b_} {}
    
    int a_;
    int b_;
};

int main() {
    S s{5};
    std::cout << s.a_ << ' ' << s.b_;
}