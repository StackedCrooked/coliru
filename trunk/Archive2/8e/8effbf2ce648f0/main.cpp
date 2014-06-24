#include <iostream>

struct B
{ 
    int i; 
    B(): i(10) { std::cout << __PRETTY_FUNCTION__ << ' ' << this << std::endl; }
    operator int&() { return i; } 
    ~B() { std::cout << __PRETTY_FUNCTION__ << ' ' << this << std::endl; }
};

int main()
{
    int& ri = B();
    std::cout << ri << '\n';
}
