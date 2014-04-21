#include <algorithm>
#include <bitset>
#include <functional>
#include <ios>
#include <iterator>
#include <iostream>

int main() 
{
    std::bitset<64> map[4];
    
    std::cout << std::hex << std::uppercase;
    
    for(auto const& m : map) {
        std::cout << m.to_ulong() << '\n';
    }
    
    std::for_each(std::begin(map), std::end(map), [](std::bitset<64>& m) { m.set(); });
    
    for(auto const& m : map) {
        std::cout << m.to_ulong() << '\n';
    }
}
