#include <iostream>
#include <cstdlib>

struct chameleon
{
    template<typename T>
    constexpr operator T() const
    {
        return T{};
    }

    constexpr chameleon() = default;
};

template<std::size_t I>
struct placeholder : public chameleon
{
//    constexpr placeholder() = default;
    constexpr placeholder() {}
};

constexpr const placeholder<0> _1;

template<int foo>
struct bar
{};

using mytype = bar<chameleon{}>;
using mytype2 = bar<_1>;

int main()
{}
