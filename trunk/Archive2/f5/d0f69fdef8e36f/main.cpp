#pragma once

#include <iostream>
namespace foo
{
    class boo
    {
        void somemethod();
    };
}

namespace doo
{
    void foo::boo::somemethod()
    {
        std::cout << "Hey, it works"; 
    }
}

int main()
{
    foo::boo b;
    b.somethod();
}