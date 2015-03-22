#include <vector>
#include <boost/range/algorithm_ext/erase.hpp>
#include <iostream>

int main()
{
    std::vector<int> v = {0, -1, 2, -3, 4, -5, 6, -7};
    for(auto const i : v) std::cout << i << ", ";
    std::cout << "\n";
    
    boost::remove_erase_if(v, [](int i){ return i < 0; });
    
    for(auto const i : v) std::cout << i << ", ";
    std::cout << "\n";
}