#include <iostream>
#include <string>
#include <limits>
#include <boost/multiprecision/cpp_int.hpp>

int main()
{
    std::cout << std::numeric_limits<long long>::max() << '\n' ; // typically 9223372036854775807
    std::cout << std::numeric_limits<unsigned long long>::max() << '\n' ; // typically 18446744073709551615

    {
        int i = 15 ;
        unsigned long long n = 1 ;
        while( i > 1 ) { n *= i ; --i ; }
        std::cout << "15! == " << n << '\n' ;

        const std::string str = std::to_string(n) ;
        std::cout << str.size() << " digits\n" ;
    }

    {
        int i = 50 ;
        boost::multiprecision::cpp_int n = 1 ;
        while( i > 1 ) { n *= i ; --i ; }
        std::cout << "50! == " << n << '\n' ;

        const std::string str = n.str() ;
        std::cout << str.size() << " digits\n" ;
    }
}
