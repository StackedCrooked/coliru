#include <cstdlib>
#include <iostream>
 
int main()
{
    std::cout << std::strtod("0.0000000123", nullptr) << "\n";
 
    // the second arg of strto* is non-const. We must copy the string
    char src[] = "0.012  15e16 -0x1afp-2 inF Nan";
    char* c = src;
 
    std::cout << std::strtod(c, &c) << "\n";
    std::cout << std::strtod(c, &c) << "\n";
    std::cout << std::strtod(c, &c) << "\n";
    std::cout << std::strtod(c, &c) << "\n";
    std::cout << std::strtod(c, &c) << "\n";
    double a = std::strtod("Nan",NULL);
    std::cout<<a<<std::endl;
}