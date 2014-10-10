#include <iostream>

namespace a
{
    struct C
    {
        enum class B {
            b
        };
    };
    struct A
    {
        void test()
        {
            using C::B;
            B::b;
        }
    };
}

int main()
{
}