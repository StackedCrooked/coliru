#include <iostream>
#include <boost/rational.hpp>
#include <boost/multiprecision/cpp_int.hpp>

template < typename INTEGER_TYPE = int > using rational = boost::rational<INTEGER_TYPE> ;

int main()
{
    rational<> a = 7 ; // 7/1
    rational<> b( 44, 14 ) ; // 22/7
    rational<> c = a*a + b*b - 2*a*b ;
    std::cout << a << '\n' << b << '\n' << c << '\n' ;
    
    using boost::multiprecision::cpp_int ;
    rational<cpp_int> d( cpp_int("12345678987654321"), cpp_int("123456789") ) ;
    std::cout << d << '\n' << d + 25000000 << '\n' ;
    
    std::cout << d / boost::rational_cast<cpp_int>(c) << '\n' ;
    
}
