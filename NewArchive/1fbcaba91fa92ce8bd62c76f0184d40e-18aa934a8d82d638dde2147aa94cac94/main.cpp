#include <iostream>

namespace test {
    namespace a { void foo() { std::cout << "test::a" << std::endl; } }
    inline namespace b { void foo() { std::cout << "test::b" << std::endl; } }
}

int main()
{
    using namespace test;
    foo();
}