#include <iostream>

struct S
{
    S()    noexcept = default;
    S(S&&) noexcept { std::cout << "move-ctor"; }
};

void f(S) {}

int main()
{
    f(S{});
}