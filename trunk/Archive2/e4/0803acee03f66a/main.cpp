#include <boost/fusion/adapted/std_tuple.hpp>
#include <boost/fusion/include/algorithm.hpp>
#include <boost/phoenix/phoenix.hpp>

using namespace boost::phoenix::arg_names;

#include <iostream>

int main()
{
    auto t = std::make_tuple(1, 3.4, 5.f); 

    std::cout << boost::fusion::accumulate(t, 0, arg1 + arg2) << std::endl;
    std::cout << boost::fusion::accumulate(t, 1, arg1 * arg2) << std::endl;
}

