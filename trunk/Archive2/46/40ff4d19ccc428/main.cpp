#include <iostream>

template<int N>
struct foo {
    constexpr foo() : a() {}
    int a[N + 1];
};

int main() {
    foo< (foo<1>{}).a[0] > f;
}