
#include <sstream>
#include <iostream>

int main()
{
    std::string s1 = static_cast<std::ostringstream&>(std::ostringstream() << "XYZ").str();
    std::string s2 = static_cast<std::ostringstream&>(std::ostringstream() << "XYZ" << "ABC").str();
    
    std::cout << "s1: " << s1 << std::endl;
    std::cout << "s2: " << s2 << std::endl;
}