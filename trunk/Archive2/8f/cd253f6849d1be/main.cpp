#include <boost/fusion/adapted/std_tuple.hpp>
#include <boost/fusion/include/algorithm.hpp>
#include <boost/phoenix/phoenix.hpp>

using namespace boost::phoenix::arg_names;

#include <iostream>

int main()
{
    auto t = std::make_tuple(5, 3.2, 7, 6.4f); 

    std::cout << boost::fusion::accumulate(t, 0, arg1 + arg2) << std::endl;
    std::cout << boost::fusion::accumulate(t, 1, arg1 * arg2) << std::endl;
}

