#include <iostream>

[[deprecated("test")]]
void foo()
{
}

int main()
{
    auto f = [] (auto x) { std::cout << x; };
    f(3);
    f("hello");
    foo();
}