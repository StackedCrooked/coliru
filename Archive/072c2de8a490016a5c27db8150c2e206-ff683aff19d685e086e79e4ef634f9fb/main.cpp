#include <iostream>

struct S
{
    S() = default;
    S(S const &)
    {
        std::cout << "copy\n";
    }
};

void f(S const &) {}

int main()
{
    S s{};
    f( s );
}