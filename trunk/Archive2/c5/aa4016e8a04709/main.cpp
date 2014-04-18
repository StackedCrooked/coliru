#include <iostream>
#include <cstdint>
#include <vector>
#include <typeinfo>

int main()
{
    // make a vector of X's
    std::vector<std::uint8_t> items = { 0, 1, 2, 3 };
    for (auto x : items)
    {
        std::cout << std::boolalpha << (typeid(x) == typeid(std::uint8_t)) << std::endl;
    }
    
}
