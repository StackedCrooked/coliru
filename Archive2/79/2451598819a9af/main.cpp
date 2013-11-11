#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>
#include <sstream>

int main()
{
    boost::multiprecision::cpp_int n = 12345678 ;
    for( int i = 0 ; i < 10 ; ++i ) n = n * n ;

    std::ostringstream stm ;
    stm << n ;
    const std::string str = stm.str() ;

    std::cout << "the number has " << str.size() << " digits.\n" ;
}
