
#include <sstream>
#include <iostream>

int main()
{
    auto s1 = static_cast<std::stringstream&>(std::stringstream() << "XYZ").str();
    auto s2 = static_cast<std::stringstream&>(std::stringstream() << "XYZ" << "ABC").str();
    
    std::cout << "s1: " << s1 << std::endl;
    std::cout << "s2: " << s2 << std::endl;
}