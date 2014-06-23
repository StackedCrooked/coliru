#include <iostream>

struct B
{ 
    int i; 
    B(): i(10) {} 
    operator int&() { return i; } 
    ~B() { std::cout << __PRETTY_FUNCTION__ << std::endl; }
};

int main()
{
    int& ri = B();
    std::cout << ri << '\n';
}
