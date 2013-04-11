#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <utility>
#include <vector>


std::ostream& operator<<(std::ostream& os, const std::vector<int> & data)
{
    for (auto & n : data)
    {
        os << n << " ";
    }
    return os;
}

int main()
{
    auto size = 1000000u;
    
    std::cout << "Generate vector of size " << size << "..." << std::endl;
    std::vector<int> v;
    while (v.size() != size)
    {
        v.push_back(v.size());
    }
    
    std::cout << "Shuffling..." << std::endl;
    std::random_shuffle(v.begin(), v.end());
    std::cout << v << std::endl;
    
    
    std::cout <<"Sorting..." << std::endl;    
    std::sort(v.begin(), v.end());
    std::cout << v << std::endl;
}