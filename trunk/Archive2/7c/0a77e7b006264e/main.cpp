#include <iostream>
#include <type_traits>

template<bool b, class c = void>
using enable_if_t = typename std::enable_if<b, c>::type;

template<int Version>
struct foo
{
    constexpr static bool is_valid = false;
};

struct helper { constexpr static bool is_valid = true; };

template<>
struct foo<0> : helper
{
    static void print() { std::cout <<"version 0\n"; }
};

template<>
struct foo<2> : helper
{
    static void print() { std::cout <<"version 2\n"; }
};


template<int Version>
struct foo_selector
{
    template<class T>
    struct wrap { using type = T; };
    using type = typename std::conditional<foo<Version>::is_valid, wrap<foo<Version>>, foo_selector<Version-1>>::type::type;
};

template<int Version>
using select_foo = typename foo_selector<Version>::type;

int main()
{
    select_foo<1>::print();
    select_foo<3>::print();
}