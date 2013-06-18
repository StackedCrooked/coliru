#include <sstream>
#include <iostream>
#include <iomanip>

int main()
{
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(2) << 10;
    ss << " - ";
    ss << std::setfill('0') << std::setw(2) << 5;
    
    std::cout << ss.str();
}