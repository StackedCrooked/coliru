#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>
// http://www.boost.org/doc/libs/1_55_0/libs/multiprecision/doc/html/boost_multiprecision/tut/ints/cpp_int.html

int main()
{
    using namespace boost::multiprecision ;
    
    // unsigned integer, 256-bit fixed precision, unchecked
    uint512_t i( "115792089237316195423570985008687907853269984665640564039457584007908834671663" ) ;
    std::cout << i << "\n\n" ;

    // unsigned integer, 512-bit fixed precision, checked
    checked_uint512_t j = checked_uint512_t(1U) << 511 ;
    std::cout << j << "\n\n" ;
    
    try { j <<= 1 ; }
    catch( const std::exception& e ) { std::cerr << "*** error: " << e.what() << "\n\n" ; }
    
    // signed integer, arbitrary precision
    cpp_int k = cpp_int(i) * j ;
    std::cout << k << "\n\n" ;
}
