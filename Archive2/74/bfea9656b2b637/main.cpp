#include <iostream>
#include <cmath>

template <typename RoundingStrategy = std::round> int convert(float a)
{
    return RoundingStrategy(a);   
}

int main()
{
    std::cout << convert(4.5) << std::endl;
}
