#include <type_traits>
#include <iostream>

template< class T >
constexpr T&& forward( typename std::remove_reference<T>::type& t )
{
    std::cout << __PRETTY_FUNCTION__ << '\n';
    return static_cast<T&&>(t);
}

template< class T >
constexpr T&& forward( typename std::remove_reference<T>::type&& t )
{
    std::cout << __PRETTY_FUNCTION__ << '\n';
    return static_cast<T&&>(t);
}

void g(int&)  { std::cout << __PRETTY_FUNCTION__ << '\n'; }
void g(int&&) { std::cout << __PRETTY_FUNCTION__ << '\n'; }

template<class T>
auto f(T&& t)
{
    std::cout << __PRETTY_FUNCTION__ << '\n';
    g(forward<decltype(forward<T>(t).get())>(forward<T>(t).get()));
}

struct foo
{
    int i = 42;
    int  get() && { std::cout << __PRETTY_FUNCTION__ << '\n'; return i; }
    int& get() &  { std::cout << __PRETTY_FUNCTION__ << '\n'; return i; }
};

#include <utility>

int main()
{
    foo foo1;
    f(foo1);
    std::cout << "------" << '\n';
    f(std::move(foo1));
}
