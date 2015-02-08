#include <iostream>
#include <iomanip>

int main()
{
    double d = 123.45678 ;

    std::cout << '|' << std::fixed << std::setprecision(3) << d << "|\n" ; // |123.457|

    std::cout << '|' << std::left << std::setw(15) << d << "|\n" ; // |+123.457       |

    std::cout << std::showpos << std::setfill('0')  ;

    std::cout << '|' << std::left << std::setw(15) << d << "|\n" ; // |+123.4570000000|

    std::cout << '|' << std::right << std::setw(15) << d << "|\n" ; // |0000000+123.457|

    std::cout << '|' << std::internal << std::setw(15) << d << "|\n" ; // |+0000000123.457|
}
