#include <boost/tuple/tuple.hpp>
#include <boost/fusion/adapted/boost_tuple.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <boost/spirit/include/phoenix.hpp>
using boost::phoenix::arg_names::arg1;
#include <iostream>

int main()
{
    boost::fusion::for_each(boost::make_tuple("hello", 42, "universe", "fwoop"), std::cout << arg1 << std::endl);
}