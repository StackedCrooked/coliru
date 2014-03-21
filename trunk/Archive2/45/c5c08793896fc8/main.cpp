#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>

int main()
{
    const boost::multiprecision::cpp_int max = 6;
    const boost::multiprecision::cpp_int factor = 4;
    const boost::multiprecision::cpp_int result = factor * factor * (max/factor); //should be 4 * 4 * (6/4) == 4 * 4 * (1) == 16 * 1 == 16
    
    std::cout << max << '/' << factor << " = " << max/factor << std::endl;
    std::cout << result << std::endl;
    
    const boost::multiprecision::cpp_int result2 = 4 * 4 * (6/4);
    
    std::cout << result2 << std::endl;
}