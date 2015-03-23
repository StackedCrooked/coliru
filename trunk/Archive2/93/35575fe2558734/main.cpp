#include <iostream>

#include <cstdlib>

#define PRINT_NAME { std::cout << __PRETTY_FUNCTION__ << std::endl; }

namespace
{

struct A 
{
    A() { PRINT_NAME; }
    ~A() { PRINT_NAME; }
};

A f() { return {}; }

A b;

const A& g() { return b; }

}

int
main()
{ 
    std::cout << "------------------" << std::endl;
    {
        f();
        std::cout << 1 << std::endl;
    }
    std::cout << "------------------" << std::endl;
    {
        const A& a = f();
        std::cout << 2 << std::endl;
    }
    std::cout << "------------------" << std::endl;
    {
        const A& a = g();
        std::cout << 3 << std::endl;
    }
    std::cout << "------------------" << std::endl;
    return EXIT_SUCCESS;
}