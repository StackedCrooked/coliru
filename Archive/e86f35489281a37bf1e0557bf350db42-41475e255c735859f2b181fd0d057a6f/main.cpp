#include <iostream>

struct S
{
    S() = default;
    S(S const &) noexcept { std::cout << "copy-ctor"; }
    S(S&&)       noexcept { std::cout << "move-ctor"; }
};

S f()
{
    S s;
    return s;
}

int main()
{
    f();
}