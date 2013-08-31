#include <boost/phoenix/core.hpp>
#include <boost/phoenix/operator.hpp>
#include <boost/phoenix/function.hpp>
#include <iostream>


boost::phoenix::expression::argument<1>::type arg1;

auto inc  = arg1 + 1;
auto twice = arg1 + arg1;
auto twice_after_inc = twice(inc(arg1));


int main()
{
    std::cout << twice_after_inc(1) << std::endl;
}