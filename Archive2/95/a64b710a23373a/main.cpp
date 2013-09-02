#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/phoenix/phoenix.hpp>

using namespace boost::adaptors;
using namespace boost::phoenix::arg_names;

#include <vector>
#include <iostream>
#include <iterator>

int main()
{
    const std::vector<int> v { 1,2,3,-99,4 };

    boost::for_each(v | filtered(arg1 % 2 == 0), std::cout << arg1 << "\n");
}
