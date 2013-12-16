#include <iostream>

constexpr int x = 0;

template <int...> struct test {};

test<(&x - &x)> foo;

int main() {}