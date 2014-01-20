#include <bitset>
#include <iostream>
#include <iomanip>

template<size_t bits>
std::bitset<bits> subset(std::bitset<bits> set, int min, int max)
{
    std::bitset<bits> range = ~std::bitset<bits>();
    const int ignore_hi = bits-max;
    range = (range << ignore_hi) >> ignore_hi;
    set &= range;
    return set >> min;
}

int main() {
    std::bitset<1024> start;
    start |= std::bitset<1024>(0xFFFFFFFF)<<(1024-32);
    start |= std::bitset<1024>(0xAAAAAAAA)<<(500);
    start |= std::bitset<1024>(0x77777777);
    
    unsigned long long A = subset(start, 1024-32, 1024).to_ullong();
    unsigned long long B = subset(start, 500, 532).to_ullong();
    unsigned long long C = subset(start, 0, 32).to_ullong();
    
    std::cout << std::hex << A << ' ' << B << ' ' << C;    
}