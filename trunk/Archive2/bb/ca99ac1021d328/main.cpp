#include <utility>
#include <iostream>

void foo() { std::cout << "global"; }

struct X
{
    void bar() { []foo(); } // Prints "global"?
    void bar() { [this]foo(); } // Prints "member"?
    void foo() { std::cout << "member"; }
};

int main()
{
    X x;
    x.bar();
}