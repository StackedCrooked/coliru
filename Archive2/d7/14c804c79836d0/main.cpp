#include <iostream>
#include <sstream>
 
int main()
{
    std::cout << "The number 0.01 in fixed:      " << std::fixed << 0.01 << '\n'
              << "The number 0.01 in scientific: " << std::scientific << 0.01 << '\n'
              << "The number 0.01 in hexfloat:   " << std::hexfloat << 0.01 << '\n'
              << "The number 0.01 in default:    " << std::defaultfloat << 0.01 << '\n';
    double f;
    std::istringstream("0x1P-1022") >> std::hexfloat >> f;
    std::cout << "Parsing 0x1P-1022 as hex gives " << f << '\n';
}