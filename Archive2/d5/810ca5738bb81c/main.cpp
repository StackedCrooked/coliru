#include <iostream>
#include <sstream>
#include <iomanip>

int main(void)
{
    static_assert(sizeof(unsigned long)==sizeof(double), "DO SOMETHING ELSE");
    
    {
        unsigned long ua = 0x7FEFFFFFFFFFFFFFul;
        unsigned long ub = 0x7FEFFFFFFFFFFFFEul;
        double a = *((double*)&ua);
        double b = *((double*)&ub);
        double c = a - b;
        double d = 2 / c;
        
        std::cout << std::setprecision(30) << a << '\n' << b << '\n' << c << '\n' << d << '\n';
    }
    {
        unsigned long ua = 0x1ul;
        unsigned long ub = 0x2ul;
        double a = *((double*)&ua);
        double b = *((double*)&ub);
        double c = a - b;
        double d = 2 / c;
        
        std::cout << std::setprecision(30) << a << '\n' << b << '\n' << c << '\n' << d << '\n';
    }
}