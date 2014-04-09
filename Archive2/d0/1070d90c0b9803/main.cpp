#include <iostream>

template<typename T> void f(T x) { std::cout << x << std::endl; }

int main()
{
    auto x = 5;
    f(x);
}
