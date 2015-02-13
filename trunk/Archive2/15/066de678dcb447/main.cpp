#include <iostream>
#include <string>
#include <memory>
#include <sstream>

struct meow
{
    bool foo{};
};

struct kitty
{
};

namespace detail
{
    template <typename T>
    auto constexpr has_foo(int&&) -> decltype(std::declval<T>().foo, bool{})
    { return true; }
    template <typename T>
    bool constexpr has_foo(...)
    { return false; }
}
template <typename T>
auto constexpr has_foo()
{ return detail::has_foo<T>(0); }

int main()
{
    std::cout << has_foo<meow>() << std::endl;
    std::cout << has_foo<kitty>() << std::endl;
}