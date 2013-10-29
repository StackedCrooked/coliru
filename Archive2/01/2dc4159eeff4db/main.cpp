#include <iostream>
#include <iomanip>

int main()
{
    std::cout << std::showpos ;

    int v = 123 ; // default fill character is space
    std::cout << std::right << '|' << std::setw(6) << v << "|\n" ;
    std::cout << std::left << '|' << std::setw(6) << v << "|\n" ;
    std::cout << std::internal << '|' << std::setw(6) << v << "|\n" ;

    v = 12345678 ; // std::setw(6) ignored
    std::cout << std::right << '|' << std::setw(6) << v << "|\n" ;
    std::cout << std::left << '|' << std::setw(6) << v << "|\n" ;
    std::cout << std::internal << '|' << std::setw(6) << v << "|\n" ;

    v = 1 ;
    std::cout << std::right << '|' << std::setfill('.') << std::setw(6) << v << "|\n" ;
    std::cout << std::left << '|' << std::setfill('*') << std::setw(6) << v << "|\n" ;
    std::cout << std::internal << '|' << std::setfill('0') << std::setw(6) << v << "|\n" ;

    std::cout << std::noshowpos ;

    std::cout << std::right << '|' << std::setfill('.') << std::setw(6) << v << "|\n" ;
    std::cout << std::left << '|' << std::setfill('*') << std::setw(6) << v << "|\n" ;
    std::cout << std::internal << '|' << std::setfill('0') << std::setw(6) << v << "|\n" ;
}
