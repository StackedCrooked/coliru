#include <type_traits>

using namespace std;

struct Foo {
    constexpr Foo (int i) : i_(i) {}
    int i_;
};

constexpr int operator*(int i, Foo j) {
    return i * j.i_;
}

int main(void) {
    integral_constant<int, 2> k;

    constexpr int i = k * Foo(3);
    static_assert(i == 6, "Error!");

    constexpr int j = 2 * Foo(3);
    static_assert(j == 6, "Error!");
}