#include <iostream>

void foo(...) { std::cout << "foo(...)"; }
auto foo(int p) -> decltype(foo(p)) { std::cout << "foo(int)"; }

int main()
{
    decltype(foo(42)) i;
}
