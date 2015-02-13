#include <iostream>
#include <string>
#include <memory>
#include <sstream>

struct meow
{
    template <bool B>
    void foo();
};

struct kitty
{
};

struct bar
{
    template <typename T>
    void foo(); // not compatible
};

namespace detail
{
    template <typename T, bool B>
    auto constexpr has_foo(int) -> decltype(T::template foo<B>, bool{})
    { return true; }
    template <typename T, bool B>
    bool constexpr has_foo(...)
    { return false; }
}
template <typename T, bool B>
auto constexpr has_foo()
{ return detail::has_foo<T, B>(0); }

int main()
{
    std::cout << has_foo<meow, true>() << std::endl;
    std::cout << has_foo<kitty, true>() << std::endl;
    std::cout << has_foo<bar, true>() << std::endl;
}