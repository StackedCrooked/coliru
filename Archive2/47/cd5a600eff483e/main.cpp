#include <iostream>

#include <boost/multiprecision/cpp_dec_float.hpp>
//#include <boost/math/special_functions.hpp>

typedef boost::multiprecision::number<boost::multiprecision::cpp_dec_float<50> > flp_type;

int main()
{
    // 50 decimal digits
    flp_type const sqrt2("1.4142135623730950488016887242096980785696718753769");
    // Contains calculated guard digits
    flp_type result(sqrt(flp_type("2")));

    // The 50 digits of precision actually ompare equal
    std::cout << std::setprecision(50) << sqrt2 << std::endl;
    std::cout << std::setprecision(50) << result << std::endl;

    // Either
    std::cout << std::numeric_limits<flp_type>::epsilon() << "\n";
    std::cout << (abs(result-sqrt2) < std::numeric_limits<flp_type>::epsilon()) << std::endl;

    // Or
    result = flp_type { result.str(49, std::ios::fixed) };
    std::cout << (result==sqrt2) << std::endl;

    return 0;
}
