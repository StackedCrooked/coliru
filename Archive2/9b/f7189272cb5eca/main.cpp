#include <boost/multiprecision/number.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <iostream>

namespace mp = boost::multiprecision;

int main()
{
    using Dec = mp::cpp_dec_float_50;

    for (Dec d : { 
            Dec( "3.34"),   Dec( "3.35"),   Dec( "3.38"),
            Dec( "2.24"),   Dec( "2.25"),   Dec( "2.28"),
            Dec("-2.24"),   Dec("-2.25"),   Dec("-2.28"),
            Dec("-3.34"),   Dec("-3.35"),   Dec("-3.38"),
            })
    {
        std::cout     << d.str(2, std::ios_base::fixed) 
            << " -> " << d.str(1, std::ios_base::fixed) << "\n";
    }
}
