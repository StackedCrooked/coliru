#include <iostream>
#include <string>
#include <memory>
#include <sstream>

struct meow
{
    template <typename T, typename E = std::enable_if_t<std::is_same<T, int>::value>>
    void foo();
};

template<>
void meow::foo<int, int>() {
}

struct kitty
{
};

struct bar
{
    template <typename T, typename E = std::enable_if_t<!std::is_same<T, int>::value>>
    void foo(); // not compatible
};

namespace detail
{
    template <typename T, typename B>
    auto constexpr has_foo(int) -> decltype(T::template foo<B>, bool{})
    { return true; }
    template <typename T, typename B>
    bool constexpr has_foo(...)
    { return false; }
}
template <typename T, typename B>
auto constexpr has_foo()
{ return detail::has_foo<T, B>(0); }

int main()
{
    std::cout << has_foo<meow, int>() << std::endl;
    std::cout << has_foo<kitty, int>() << std::endl;
    std::cout << has_foo<bar, int>() << std::endl;
}