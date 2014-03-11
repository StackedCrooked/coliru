#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <boost/dynamic_bitset.hpp>

int main()
{
    std::vector<std::uint8_t> v{{ 0, 7, 4 }};
    boost::dynamic_bitset<std::uint8_t> b(v.begin(), v.end());
    std::cout << "Value: " << b << std::endl;
    for (size_t i = 0; i < b.size(); ++i)
        std::cout << b[i] << "x";
    std::cout << std::endl;
}
