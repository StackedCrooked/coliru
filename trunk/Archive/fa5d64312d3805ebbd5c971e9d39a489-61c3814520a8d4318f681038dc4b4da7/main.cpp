#include <iostream>

template <typename... T>
constexpr int foo() { return 0; }

template <int... N>
constexpr int foo() { return 0;}

int main()
{
    foo<4>();
    foo<int>();
}