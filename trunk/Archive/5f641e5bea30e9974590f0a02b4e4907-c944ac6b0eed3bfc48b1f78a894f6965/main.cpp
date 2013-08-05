#include <array>

struct foo {
    int x;
    int y;
    std::array<int, 13> zeroes;
    constexpr foo(int x, int y) : x(x), y(y), zeroes() {}
};

const foo f(1, 2);

int main() {
    const_cast<int&>(f.x) = 0;
}