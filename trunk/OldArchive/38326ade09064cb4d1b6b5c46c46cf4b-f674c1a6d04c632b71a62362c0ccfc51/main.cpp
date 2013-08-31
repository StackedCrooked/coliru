#include <boost/algorithm/gather.hpp>
#include <iostream>
#include <vector>

using boost::algorithm::gather;

std::vector<int> vec = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };


int main()
{
    
    std::cout << "Divisible by 2: " << std::endl;
    {
        auto pair = gather(begin(vec), end(vec), begin(vec) + vec.size() / 2, [](int a) { return a % 2 == 0; });        
        for (; pair.first != pair.second; ++pair.first)
        {
            std::cout << *pair.first << std::endl;
        }
    }
    
    std::cout << "Divisible by 3: " << std::endl;    
    {
        auto pair = gather(begin(vec), end(vec), begin(vec) + vec.size() / 2, [](int a) { return a % 3 == 0; });        
        for (; pair.first != pair.second; ++pair.first)
        {
            std::cout << *pair.first << std::endl;
        }
    }
    
    std::cout << "Divisible by 5: " << std::endl;    
    {
        auto pair = gather(begin(vec), end(vec), begin(vec) + vec.size() / 2, [](int a) { return a % 5 == 0; });        
        for (; pair.first != pair.second; ++pair.first)
        {
            std::cout << *pair.first << std::endl;
        }
    }
}