#include <iostream>

namespace test {
    inline namespace a { void foo(); }
    inline namespace b { void foo(); }
}

int main()
{
    using namespace test;
    foo();
}