#include <cmath>
#include <iostream>
 
int main()
{
    double base = 2.0;
    double arg  = 256.0;
    double result = std::log(arg) / std::log(base);
 
    std::cout << result << '\n';
}