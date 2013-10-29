#include <iostream>
#include <string>
#include <vector>
#include <limits>

/// Yay! I get to use g++4.8 here!
template <typename T>
using MyVector = std::vector<T>;

int main()
{    
    unsigned int max = std::numeric_limits<unsigned int>::max();
    std::cout << static_cast<int>(max) << std::endl;

    std::cout << (int)(static_cast<unsigned char>(char(-128))) << std::endl;
    
    char c = -128;
    std::cout << (int)(*reinterpret_cast<unsigned char*>(&c)) << std::endl;
}
