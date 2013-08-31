#include <iostream>
#include <string>
#include <vector>

struct A {
};


int main()
{
    A a;
    A &&ra = std::move (a);
}
