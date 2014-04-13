#include <boost/multiprecision/number.hpp>
#include <boost/multiprecision/gmp.hpp>
#include <iostream>

namespace mp = boost::multiprecision;

int main()
{
    typedef mp::number<mp::gmp_float<100>> mp_type;
    mp_type test_num("7.071067811865475244008443621048490392848359376884740365883398690000000000000000000e-01");

    std::cout << test_num.str(0, std::ios_base::scientific) << '\n';
}
