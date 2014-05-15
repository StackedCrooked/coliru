#include <boost/range/algorithm.hpp>
#include <boost/range/adaptors.hpp>

using namespace boost::adaptors;

// only for succinct predicates without lambdas
#include <boost/phoenix.hpp>
using namespace boost::phoenix::arg_names;

// for demo
#include <iostream>

int main()
{
    std::vector<int> const v { 1,2,3,4,5 };

    boost::copy(
            v | filtered(arg1 % 2) | transformed(arg1 * arg1 / 7.0),
            std::ostream_iterator<double>(std::cout, "\n"));
}
