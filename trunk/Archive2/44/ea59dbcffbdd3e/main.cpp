struct c_api {
    int a, b, c;
};

struct cpp : c_api {
    constexpr cpp(): c_api{1, 2, 3} {}
};

#include <iostream>

int main() {
    constexpr cpp x;
    static_assert(x.a == 1 && x.b == 2 && x.c == 3, "..");
    std::cout << x.a << '\n' << x.b << '\n' << x.c << '\n';
}