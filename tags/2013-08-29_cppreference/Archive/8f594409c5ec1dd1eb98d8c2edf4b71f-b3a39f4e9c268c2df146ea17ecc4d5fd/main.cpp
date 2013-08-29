#include <iostream>
#include <ios>

struct Y {};

template<class X, class Y>
struct generic { int i = 0; };

template<class X>
using Bind_CPP11 = generic<X, Y>;

template<class X, template<class> class Impl>
struct wrapper_CPP11
{
    Impl<X> foo;
};

template<class X>
struct Bind_CPP03
{
    typedef generic<X, Y> type;
};

template<class X, template<class> class Impl>
struct wrapper_CPP03
{
    typename Impl<X>::type foo;
};

int main()
{
    wrapper_CPP11<int, Bind_CPP11> w11;
    wrapper_CPP03<int, Bind_CPP03> w03;
    std::cout << std::boolalpha << (w11.foo.i == w03.foo.i) << "\n";
};