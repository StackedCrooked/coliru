#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>

template <typename T>
std::string toHex(T number)
{
    std::stringstream ss;
    ss << std::hex << number;
    return ss.str();
}

int main()
{
    std::cout << toHex(1000) << std::endl;
    
    return 0;
}