#include <iostream>
#include <functional>
#include <vector>

class A
{ 
    public:
    A() : x(42) { std::cout << "constructed "; }
    int x;
};

A& getA() {
    static A a;
    return a;
}

int main()
{
    std::cout << "started ";
    std::cout << getA().x;
}

