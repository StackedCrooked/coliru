#include <iostream>
#include <limits>
#include <utility>

template <typename T>
auto getRange()
{ 
    return std::make_pair(static_cast<int>(std::numeric_limits<T>::min()),
        static_cast<int>(std::numeric_limits<T>::max()));
}

int main()
{
    auto charRange = getRange<char>();
    std::cout << "char: [" << charRange.first << ", " << charRange.second << "]" << std::endl;
    
    auto ucharRange = getRange<unsigned char>();
    std::cout << "char: [" << ucharRange.first << ", " << ucharRange.second << "]" << std::endl;
    
    auto scharRange = getRange<signed char>();
    std::cout << "char: [" << scharRange.first << ", " << scharRange.second << "]" << std::endl;
    
    return 0;
}