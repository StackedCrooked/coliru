#include <iostream>

int main()
{
    auto f = [](int rhs, int lhs) -> int { return rhs + lhs; }; // ok
    auto g = [](int rhs, int lhs)        { return rhs + lhs; }; // ok 
    
    auto h = [](int rhs, int lhs)        { if (rhs > lhs) return 1; else return lhs; }; // ok 
    
    std::cout << f(1, 5) << std::endl;
    std::cout << g(1, 5) << std::endl;
    std::cout << h(1, 5) << std::endl;
}