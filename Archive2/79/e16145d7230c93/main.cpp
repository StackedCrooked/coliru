#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm.hpp>

using namespace boost::adaptors;

#include <vector>
#include <iostream>
#include <iterator>

int main()
{
    const std::vector<int> v { 1,2,3,-99,4 };

    boost::copy(v | filtered([](int i) { return i > 0; }),
            std::ostream_iterator<int>(std::cout, "\n"));
}
