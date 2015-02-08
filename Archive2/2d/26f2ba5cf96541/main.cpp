#include <iostream>
#include <cassert>
#include <boost/thread/once.hpp>

struct A
{
    A(int _a) : a(_a) {}
    int a;
};

enum Foo
{
    FA,
    FB
};

enum Bar
{
    BA,
    BB
};

template <Foo F, Bar = BA>
struct FooHelper
{
    static A* buzz()
    {
        assert(0);
    }
};

template<>
struct FooHelper<FA>
{
    static A* buzz()
    {
        static A a(1);
        return &a;
    }
};

template<>
struct FooHelper<FB>
{
    static A* buzz()
    {
        static A a(2);
        return &a;
    }
};

template<>
struct FooHelper<FA, BB>
{
    static A* buzz()
    {
        static A a(3);
        return &a;
    }
};

template <Foo F, Bar BAR>
void Init()
{
    FooHelper<F, BAR>::buzz();
}


boost::once_flag fa_bb_once = BOOST_ONCE_INIT;
// itd...

int main()
{
  boost::call_once(fa_bb_once, Init<FA,BB>); 
  A* dupa = FooHelper<FA,BB>::buzz();
  std::cout << dupa->a;
}
