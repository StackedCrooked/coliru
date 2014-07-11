#include <type_traits>
#include <utility>

#define FORWARD(x) \
    std::forward \
    < \
        typename std::conditional \
        < \
            std::is_rvalue_reference<decltype(x)>::value, \
            typename std::remove_reference<decltype(x)>::type, \
            decltype(x) \
        >::type \
    >(x) \
/**/

/*******************************************/

#include <iostream>

struct Foo
{
    Foo() = default;
    Foo(const Foo &)
    {
        std::cout << "copy" << std::endl;
    }
    Foo(Foo &&)
    {
        std::cout << "move" << std::endl;
    }
};

template<typename T>
void test(T &&x)
{
    Foo{std::forward<T>(x)};
    Foo{FORWARD(x)};
    std::cout << std::endl;
}

int main()
{
    Foo x;
    test(x);
    test(std::move(x));
    test(Foo{});
}