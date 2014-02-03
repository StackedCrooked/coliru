#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>

using bigint = boost::multiprecision::cpp_int ;

bigint factorial( bigint n ) { return n < 2 ? bigint(1) : n * factorial(n-1) ; }

int main()
{

    std::cout << factorial(81) << '\n' ;
}