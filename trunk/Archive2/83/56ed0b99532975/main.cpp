#include <iostream>
#include <type_traits>

template<typename T> struct foo
{};

template <typename>
struct is_foo : std::false_type {};

template <typename T>
struct is_foo<foo<T>> : std::true_type {};

template<typename, typename=void> struct aux;

template<typename Foo>
struct aux<Foo, typename std::enable_if<is_foo<Foo>::value>::type>
{
    aux() { std::cout << __PRETTY_FUNCTION__ << " 1 " << std::endl; }
};

template<typename T> struct bar : foo<T>
{};

template<typename T>
struct aux<bar<T>>
{
    aux() { std::cout << __PRETTY_FUNCTION__ << " 2 " << std::endl; }
};

int main()
{
    bar<int> b;
    aux<decltype(b)> aux1;
}
