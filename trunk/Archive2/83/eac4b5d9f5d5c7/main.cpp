#include <iostream>
#include <iterator>
#include <boost/preprocessor/repetition/enum.hpp>

constexpr double fun(double x) { return x * x; }

int main() 
{
    #define FILLER(z, i, data) fun(i)
    double constexpr a[] = { BOOST_PP_ENUM(10, FILLER, ~) };
    #undef FILLER
    
    std::copy(std::begin(a), std::end(a), std::ostream_iterator<double>(std::cout, ", ")); 
}