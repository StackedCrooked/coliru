#include <boost/algorithm/clamp.hpp>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>


using boost::algorithm::clamp;
using boost::algorithm::clamp_range;


template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}


int main()
{
    
    // Use clamp
    for (int i = 0; i != 5; ++i)
    {
        std::cout << i << " => " << clamp(i, 1, 3) << std::endl;
    }
    
    
    // Use clamp_range
    std::vector<int> original_range = { 1, 2, 3, 4, 5 };
    std::vector<int> sanitized_range;
    
    clamp_range(begin(original_range), end(original_range),
                std::back_inserter(sanitized_range), 2, 4);
                
    std::cout << "original_range : " << original_range  << std::endl;
    std::cout << "sanitized_range: " << sanitized_range << std::endl;
}

