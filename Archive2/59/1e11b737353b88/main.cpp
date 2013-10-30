
#include <sstream>
#include <iostream>

int main()
{
    std::cout << "GCC-" << __VERSION__ <<  std::endl;
    
    auto s = static_cast<std::stringstream&>(std::stringstream() << "XYZ" << "ABC").str();
    
    std::cout << s << std::endl;
}