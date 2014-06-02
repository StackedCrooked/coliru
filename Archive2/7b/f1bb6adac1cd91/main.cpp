#include <iostream>
#include <type_traits>

template<bool b>
using enable_if_t = typename std::enable_if<b>::type;

template<int Version, class, int...>
struct foo;

template<int Version, int... ii>
struct foo<Version, enable_if_t<(Version > 0)>, ii...>
{
    static void print() { std::cout << "version 0\n"; }
};

template<int Version, int... ii>
struct foo<Version, enable_if_t<(Version > 2)>, 0, ii...>
{
    static void print() { std::cout << "version 2\n"; }
};

template<int Version>
using my_foo = foo<Version, void, 0, 0, 0, 0>;

int main()
{
    my_foo<1>::print();
    my_foo<3>::print();
}