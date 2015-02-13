#include <iostream>
#include <sstream>
#include <iomanip>

int main(void)
{
    static_assert(sizeof(unsigned long)==sizeof(double), "SOMETHING ELSE");
    
    unsigned long ua = 1ul;
    unsigned long ub = 2ul;
    double a = *((double*)&ua);
    double b = *((double*)&ub);
    
    std::cout << std::setprecision(30) << a << '\n' << b << '\n';
    
     if (a == b)
     {
         std::cout << "EQUAL";
     }
     else
     {
         double c = 2 / (a - b);
         std::cout << c;
     }
}