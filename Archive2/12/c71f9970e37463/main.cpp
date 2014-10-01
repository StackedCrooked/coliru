#include <iostream>
#include <vector>
#include <iterator>
#include <functional>
#include <algorithm>

namespace std
{
    template <typename T>
    auto size(T &c)
    { return c.size(); }
    template <typename T>
    auto size(T const &c)
    { return c.size(); }
    template <typename T, std::size_t N>
    std::size_t constexpr size(T (&arr)[N])
    { return N; }
}

struct foo
{ foo(){} };

namespace std
{
    template <>
    auto size(foo &c)
    { return 42; }
    template <>
    auto size(foo const &c)
    { return 43; }
}

int main()
{
    foo f;
    std::cout << std::size(f) << std::endl;
    
    foo const fc;
    std::cout << std::size(fc) << std::endl;
}
