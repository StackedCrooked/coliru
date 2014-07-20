#include <iostream>
#include <string>
#include <type_traits>

struct base
{
    virtual ~base() = default;
};

template <typename T>
struct derived : base
{
    void work() const
    { std::cout << "derived work" << std::endl; }
};

void foo(base const &b)
{ static_cast<derived<int> const&>(b).work(); }

int main()
{
    derived<int> d;
    foo(d);
}