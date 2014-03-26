#include <boost/math/distributions.hpp>

#include <boost/tuple/tuple.hpp>
#include <boost/fusion/adapted/boost_tuple.hpp>
#include <boost/fusion/algorithm.hpp>
#include <boost/phoenix.hpp>
#include <boost/phoenix/function.hpp>

#include <iostream>

namespace bm = boost::math;
using namespace boost::phoenix::arg_names;

BOOST_PHOENIX_ADAPT_FUNCTION(double, cdf_, boost::math::cdf, 2)

int main()
{
    double x = 1.96;

    boost::fusion::for_each(
            boost::make_tuple(bm::normal(), bm::students_t(1)),
            std::cout << cdf_(arg1, x) << "\n"
            );
}
