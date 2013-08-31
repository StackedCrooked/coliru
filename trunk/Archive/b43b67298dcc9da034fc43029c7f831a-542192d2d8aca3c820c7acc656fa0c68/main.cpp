#include <algorithm>
#include <random>
#include <functional>

#include <iostream>

int main()
{
    std::mt19937                        twister(91210);
    
    // fill a vector ith [0..255]:
    std::vector<int> vNumbers(256);
    std::iota(vNumbers.begin(), vNumbers.end(), 0);
    
    // shuffle it
    std::shuffle(vNumbers.begin(), vNumbers.end(), twister);
    
    for(auto n : vNumbers)
       std::cout << n << " ";
}