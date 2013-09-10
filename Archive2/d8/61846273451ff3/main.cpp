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
    void boo::somemethod()
    {
        std::cout << "Hey, it works"; 
    }
}

int main()
{
    boo b;
    b.somethod();
}