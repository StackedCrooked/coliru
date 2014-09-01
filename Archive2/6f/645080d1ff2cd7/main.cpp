struct c_api {
    int a, b, c;
};

struct cpp : c_api {
    constexpr cpp(): c_api{1, 2, 3} {}
};

#include <iostream>

int main() {
    constexpr cpp x;
    std::cout << x.a << '\n' << x.b << '\n' << x.c << '\n';
}