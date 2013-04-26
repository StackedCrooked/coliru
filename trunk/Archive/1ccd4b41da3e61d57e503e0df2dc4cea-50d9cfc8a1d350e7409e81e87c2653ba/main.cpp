#include <type_traits>

template<bool> struct is_integer{};

template<typename T>
void do_foo(T, is_integer<true>)
{
}

template<typename T>
void do_foo(T, is_integer<false>)
{
    static_assert(!sizeof(T), "T is not int!");
}

template<typename T>
void foo(T t)
{
    do_foo(t, is_integer<std::is_integral<T>::value>{});
}

int main()
{
    foo(3);
    foo(3.2);
}