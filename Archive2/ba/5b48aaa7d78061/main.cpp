#include <iostream>
#include <iomanip> 
#include <boost/multiprecision/cpp_dec_float.hpp> 
#include <boost/math/special_functions/round.hpp>
#include <boost/format.hpp>

typedef boost::multiprecision::number<boost::multiprecision::cpp_dec_float<20>, boost::multiprecision::et_off> cpp_dec_float_20;

inline cpp_dec_float_20 dec_round(const cpp_dec_float_20& v, int p)
{
    const cpp_dec_float_20 DEC_TEN = 10;
    cpp_dec_float_20 dec_p = boost::multiprecision::pow(DEC_TEN, p); // need cache
    return boost::math::round(v * dec_p) / dec_p;
}

int main()
{
    cpp_dec_float_20 b = 8000;
    b /= 3;
    std::cout << std::setprecision(30);
    std::cout << std::numeric_limits<cpp_dec_float_20>::digits << std::endl;
    std::cout << "result = " << b << std::endl;
    std::cout << "rounded result = " << boost::math::round(b) << std::endl;
    std::cout << "rounded result = " << dec_round(b, -1) << std::endl;
    
    cpp_dec_float_20 b2("2666.67");
    cpp_dec_float_20 b3 = dec_round(b, 2);
    std::cout << " equal? " << (dec_round(b, 2) == b2) << std::endl;
    std::cout << " diff = " << (b3 - b2) << std::endl;
    std::string s = b3.str();
    std::cout << "str = " << s << std::endl;
    std::cout << "boost formated = " << boost::format("%.4f") % b3 << std::endl;
    std::cout << "boost formated = " << boost::format("%.1f") % b3 << std::endl;
    std::cout << "boost formated = " << boost::format("%f") % b3 << std::endl;
    std::cout << "boost formated = " << boost::format("%f") % (b3/100000) << std::endl;
    cpp_dec_float_20 b4 = - b3;
    std::cout << "boost formated = " << boost::format("%f") % b4 << std::endl;    
    std::cout << "stream formated = " << std::setprecision(4) << std::fixed << b3 << std::endl;
    
    return 0;
}
