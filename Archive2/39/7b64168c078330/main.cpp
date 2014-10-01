#include <iostream>
#include <limits>

int main()
{
    std::cout << "long long - size: " << sizeof(long long) << " bytes    range: "
              << std::numeric_limits<long long>::min() << " to " << std::numeric_limits<long long>::max() << "\n\n" ;

    std::cout << "double    - size: " << sizeof(double) << " bytes    range: "
              << std::numeric_limits<double>::min() << " to " << std::numeric_limits<double>::max() << "\n\n" ;

    double a = 1.0e+20 ;
    double b = 1.0e-20 ;
    double c = - a ;

    std::cout << "a: "    << a << "    a+1: "    << a+1 << "    a-1: "    << a-1 << "\n\n" ;
    std::cout << "b: "    << b << "    b+1: "    << b+1 << "    b-1: "    << b-1 << "\n\n" ;

    std::cout << "a: "    << a << "    b: "    << b << "    a+b: "    << a+b << "    a-b: "    << a-b << "\n\n" ;

    std::cout << "a: "    << a << "    b: "    << b << "    c: "    << c << "    a+b+c: "    << a+b+c << "    a+c+b: "    << a+c+b << "\n\n" ;
}
