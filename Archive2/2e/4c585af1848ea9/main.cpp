
#include <iostream>

#include <boost/multiprecision/cpp_dec_float.hpp>
//#include <boost/math/special_functions.hpp>

typedef boost::multiprecision::number<boost::multiprecision::cpp_dec_float<50> > flp_type;

int main(int argc, char* argv[])
{
    // 50 decimal digits
    flp_type sqrt2("1.4142135623730950488016887242096980785696718753769");
    // Contains calculated guard digits
    flp_type result(boost::multiprecision::sqrt(flp_type("2")));
    
    // The 50 digits of precision actually ompare equal
    std::cout << std::setprecision(50) << sqrt2 << std::endl;
    std::cout << std::setprecision(50) << result << std::endl;
    // I want this to compare to the specified precision of the type, not the guard digits
    std::cout << (result==sqrt2) << std::endl;

	return 0;
}
