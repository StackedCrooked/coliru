#include <algorithm>
#include <random>
#include <functional>

#include <iostream>

int main()
{
    std::mt19937                        twister(91210);
    std::uniform_int_distribution<int>  distribution(0,255);
    
    // fill a vector ith [0..255]:
    std::vector<int> vNumbers(256);
    std::iota(vNumbers.begin(), vNumbers.end(), 0);
    
    // shuffle it
    std::random_shuffle(vNumbers.begin(), vNumbers.end(), std::bind(distribution, twister));
    
    for(auto n : vNumbers)
       std::cout << n << " ";
}