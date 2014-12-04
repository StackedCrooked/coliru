#include <iostream>
#include <iomanip>

int main()
{
    double a = 10.01 ;
    double b = 10.00 ;

    // this may not (is very unlikely to) give 0.01 as the result.
    // it will be quite close to 0.01, but may not be exactly 0.01
    // could be either a wee bit lower than 0.01 or a wee bit higher than 0.01
    std::cout << std::setprecision(16) << a-b << '\n' ; // 0.009999999999999787

    a = 100.01 ;
    b = 100.00 ;
    std::cout << std::setprecision(16) << a-b << '\n' ; // 0.01000000000000512

    a = 1000.01 ;
    b = 1000.00 ;
    std::cout << std::setprecision(16) << a-b << '\n' ; // 0.009999999999990905

    a = 1000000.01 ;
    b = 1000000.00 ;
    std::cout << std::setprecision(16) << a-b << '\n' ; // 0.01000000000931323
}
