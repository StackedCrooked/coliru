#include <boost/phoenix/core.hpp>
#include <boost/phoenix/operator.hpp>
#include <boost/phoenix/function.hpp>
#include <iostream>


//struct increment_impl
//{
//    typedef int result_type;
//    struct result { typedef result_type type; };
//
//    result_type operator()(int n) const
//    {
//        return n + 1;
//    }
//};


//boost::phoenix::function<increment_impl> inc;

boost::phoenix::expression::argument<1>::type a;
auto inc = a + 1;
auto inc2 = inc(inc(a));


int main()
{
    std::cout << "Begin" << std::endl;
    std::cout << inc2(1) << std::endl;
    std::cout << "End" << std::endl;
}