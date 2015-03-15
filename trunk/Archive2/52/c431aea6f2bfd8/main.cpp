#include <iostream>

template<typename T>
class showDT;

auto doStuff(double const a, double const b) noexcept
{
    return (a * b) / 1.23;
}

int main(void)
{
    auto f = [](double const a){ return doStuff(a, 3); };
    
    std::cout << f(2) << std::endl;
    std::cout << doStuff(2, 3) << std::endl;
    
    return 0;
}