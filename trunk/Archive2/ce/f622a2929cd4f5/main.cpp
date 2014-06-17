#include <boost/multiprecision/number.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <iostream>

namespace mp = boost::multiprecision;

int main()
{
    typedef mp::number<mp::cpp_dec_float<100>> mp_type;
    mp_type test_num("7.0710678");
    
    test_num = test_num * mp_type.two();
    
    std::cout << test_num.str( 0, std::ios_base::scientific ) << '\n';
}
