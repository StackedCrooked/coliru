#include <boost/make_shared.hpp>

#define NOINLINE __attribute__ ((noinline))

template<int>
NOINLINE void ASM_MARKER()
{
    volatile auto anti_opti = 11;
    (void)anti_opti;
}

struct Foo
{
    int data;
};

template<int tag,typename T>
NOINLINE void test(const T &p)
{
    volatile auto anti_opti=0;
    ASM_MARKER<tag+0>();
    anti_opti = p->data;
    anti_opti = p->data;
    ASM_MARKER<tag+1>();
    (void)anti_opti;
}

int main()
{
    {
        auto p = new Foo;
        test<1000>(p);
        delete p;
    }
    {
        test<2000>(boost::make_shared<Foo>());
    }
}