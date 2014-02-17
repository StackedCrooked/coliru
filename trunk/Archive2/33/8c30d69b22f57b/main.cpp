#include <iostream>

#define TRACE std::cout << __PRETTY_FUNCTION__ << std::endl;


namespace X { struct Y {}; } using X::Y;


void foo(Y) { TRACE }


namespace Test
{
    void test1() { foo(Y{}); } // ok
    
    void foo(int) { }

    void test2() { foo(Y{}); } // identical to test1
}
