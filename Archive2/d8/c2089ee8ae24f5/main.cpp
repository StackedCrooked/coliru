# include <cstdlib>
# include <cstdio>
# include <iostream>
# include <string>
# include <sstream>

int main()
{
    const std::string str("60px;");
    float aValue = -1;
    std::istringstream ss(str);      
    ss >> aValue;
    std::cout << "stringstream: " << bool(ss) << ' '<< aValue << std::endl;
    
    const int result = std::sscanf(str.c_str(), "%g", & aValue);
    std::cout << "sscanf: " << result << ' ' << aValue << std::endl;
    
    std::cout << "strtold: " << std::strtold(str.c_str(), nullptr) << std::endl;
}
