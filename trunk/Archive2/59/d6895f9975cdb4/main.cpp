#include <iostream>

#define TRACE std::cout << __PRETTY_FUNCTION__ << std::endl;


namespace X { struct Y {}; } using X::Y;


void foo(Y) { TRACE }


namespace Test
{
    // ok
    void test1() { foo(Y{}); }

    // introduce overload
    void foo(int) { }

    // error: cannot convert 'X::Y' to 'int' for argument '1' to 'void Test::foo(int)'
    void test2() { foo(Y{}); }
}
