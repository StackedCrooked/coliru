#include <iostream>

struct y
{
};

struct x
{
    x (y blah) {std::cout << "construct x from y\n";}
};

void foo (x)
{
}

int main()
{
    y bar;
    foo(bar);
    return 0;
}
