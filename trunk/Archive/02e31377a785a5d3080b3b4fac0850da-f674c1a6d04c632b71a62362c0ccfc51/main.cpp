#include <array>
#include <limits>
#include <iostream>


struct Block
{
};

int main()
{
    std::array<int, -1UL> data;
    std::cout << "Data size: " << data.size() << std::endl;
    
    data[42] = 3;
    std::cout << data[42] << std::endl;
}