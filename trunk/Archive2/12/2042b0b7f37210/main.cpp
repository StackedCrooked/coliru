#include <boost/phoenix/core.hpp>
#include <boost/phoenix/operator.hpp>
#include <complex>
#include <iostream>

int main()
{
    using namespace boost::phoenix;
    using namespace boost::phoenix::arg_names;
    
    const auto cube = arg1 * arg1 * arg1 ;
    const auto square = arg1 * arg1 ;
    const auto half = arg1 / 2.0 ;
    
    const auto function = 2*cube + 3*square + half ;
    
    int n = 7 ;
    std::cout << function(n) << '\n' ; // 2 * cube(n) + 3 * square(n) + half(n) == 836.5
    
    n = 2 ;
    std::cout << function(n) << '\n' ; // 29
    
    std::cout << function(3.8) << '\n' ; 
}
