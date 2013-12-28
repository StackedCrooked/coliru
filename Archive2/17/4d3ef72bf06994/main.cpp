#include <utility>
#include <iostream>

void foo() { std::cout << "global"; }

struct X
{
    void bar1() { []foo(); } // Prints "global"?
    void bar2() { [this]foo(); } // Prints "member"?
    void foo() { std::cout << "member"; }
};