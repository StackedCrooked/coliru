#include <iostream>
#include <cstdint>
#include <iomanip>

template <typename ItemType>
ItemType G(ItemType i)
{
    return i - 1.5;
}

int main() 
{
    //std::cout <<  G(10) << '\n';
    //std::cout <<  std::fixed << G(1.5) << '\n';
    std::cout <<  G(UINT64_MAX) << '\n';
    std::cout << UINT64_MAX << '\n';
    
    // repro
    double x = UINT64_MAX;
    decltype(UINT64_MAX) y = x - 1.5;
    std::cout << y << '\n';
}