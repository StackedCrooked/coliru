#include <boost/multiprecision/number.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <iostream>

namespace mp = boost::multiprecision;

template <int decimals = 0, typename T>
T round_towards_zero(T const& v)
{
    static const T scale = pow(T(10), decimals);

    if (v.is_zero())
        return v;

    // ceil/floor is found via ADL and uses expression templates for optimization
    if (v<0)
        return ceil(v*scale)/scale;
    else
        // floor is found via ADL and uses expression templates for optimization
        return floor(v*scale)/scale;
}


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
        std::cout << std::showpos << round_towards_zero<2>(d) << "\t";
        std::cout << std::showpos << round_towards_zero<1>(d) << "\t";
        std::cout << std::showpos << round_towards_zero<0>(d) << "\n";
    }
}
