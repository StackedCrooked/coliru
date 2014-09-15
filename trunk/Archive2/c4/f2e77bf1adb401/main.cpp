#include <boost/multiprecision/number.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <iostream>

namespace mp = boost::multiprecision;

int main()
{
    using Int = mp::cpp_int;

    // let's think of a nice large number
    Int n = 1;
    for (Int f = 44; f>0; --f)
        n *= f;

    std::cout << n << "\n\n"; // print it for vanity 

    // let's convert it to cpp_dec_float
    // and... do something with it
    using Dec = mp::number<mp::cpp_dec_float<0> >;
    std::cout << n.convert_to<Dec>();
}
