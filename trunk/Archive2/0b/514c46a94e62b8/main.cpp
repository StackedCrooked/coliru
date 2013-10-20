#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>

int main()
{
    using bigint = boost::multiprecision::cpp_int ;

    bigint i( "1234567890987654321" ) ;

    std::cout << i * 12345 << '\n' ;
}
