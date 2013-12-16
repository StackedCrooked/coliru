#include <iostream>

constexpr int x = 0;

template <int...> struct test {};

test<(std::addressof(x) - std::addressof(x))> foo;

int main() {}