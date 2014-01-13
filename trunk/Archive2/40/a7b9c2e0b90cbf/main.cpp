#include <iostream>
#include <sstream>

int main()
{
    std::istringstream iss("1 -2 3");
    
    
    unsigned int u;    
    iss >> u; std::cout << static_cast<bool>(iss) << iss.good() << iss.fail() << iss.bad() << iss.eof() << '\n';    
    iss >> u; std::cout << static_cast<bool>(iss) << iss.good() << iss.fail() << iss.bad() << iss.eof() << '\n';    
    iss >> u; std::cout << static_cast<bool>(iss) << iss.good() << iss.fail() << iss.bad() << iss.eof() << '\n';
    
    return 0;
}
