#include <iostream>
#include <iomanip> 
#include <boost/multiprecision/cpp_dec_float.hpp> 

using namespace boost::multiprecision;

int main()
{
    double d = 20001499920014999;
    std::cout << std::setprecision(20);
    std::cout << d << std::endl;    // output: 20001499920015000
    d = 2001499920014999;
    std::cout << d << std::endl;    // output: 2001499920014999
    
    double d1 = 0.1, d2 = 0.1, d3 = 0.1, d4 = 0.3;
    double d0 = d1 + d2 + d3 - d4;  // 0.1 + 0.1 + 0.1 - 0.3
    std::cout << d1 << std::endl;  // output: 0.10000000000000000555
    std::cout << d0 << std::endl;  // output: 5.5511151231257827021e-17
    
    //boost::cpp_dec_float_50
    
    // Operations at fixed precision and full numeric_limits support:
    typedef number<cpp_dec_float<10> > cpp_dec_float_10;
    cpp_dec_float_10 b = 2;
    std::cout << std::numeric_limits<cpp_dec_float_50>::digits << std::endl;
    // Note that digits10 is the same as digits, since we're base 10! :
    std::cout << std::numeric_limits<cpp_dec_float_50>::digits10 << std::endl;
    std::cout << std::numeric_limits<cpp_dec_float_50>::max_digits10 << std::endl;
    // We can use any C++ std lib function, lets print all the digits as well:
    std::cout << std::setprecision(std::numeric_limits<cpp_dec_float_50>::max_digits10)
       << log(b) << std::endl; // print log(2)
    std::cout << "-----------------" << std::endl;
    b = b*40000000000000/3;
    b = b*100000000000;
    b = b*100000000000;
    b = b*100000000000;
    std::cout << std::setprecision(std::numeric_limits<cpp_dec_float_50>::max_digits10)
       << b << std::endl; // print log(2)
    std::cout << "size of float_10 = " << sizeof(cpp_dec_float_10) << std::endl;
    std::cout << "size of float_XX = " << sizeof(b) << std::endl;
    std::cout << "size of float_100 = " << sizeof(cpp_dec_float_100) << std::endl;
    
    typedef number<cpp_dec_float<20> > cpp_dec_float_20;
    typedef number<cpp_dec_float<20, boost::int16_t> > cpp_dec_float_20x;
    typedef number<cpp_dec_float<30> > cpp_dec_float_30;
    typedef number<cpp_dec_float<50> > cpp_dec_float_50;
    std::cout << "size of float_20 = " << sizeof(cpp_dec_float_20) << std::endl;
    std::cout << "size of float_20x= " << sizeof(cpp_dec_float_20x) << std::endl;
    std::cout << "size of float_30 = " << sizeof(cpp_dec_float_30) << std::endl;
    std::cout << "size of float_50 = " << sizeof(cpp_dec_float_50) << std::endl;
    
    return 0;
}
