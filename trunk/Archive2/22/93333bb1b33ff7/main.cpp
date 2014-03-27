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
    typedef boost::tuple<bm::normal, bm::students_t> Dists;
    Dists dists(bm::normal(), bm::students_t(1));

    double x = 1.96;

    boost::fusion::for_each(dists, std::cout << cdf_(arg1, x) << "\n");

    std::cout << "\nComposite (multiplication):\t" << boost::fusion::accumulate(dists, 1.0, arg1 * cdf_(arg2, x));
    std::cout << "\nComposite (mean):\t\t"         << boost::fusion::accumulate(dists, 0.0, arg1 + cdf_(arg2, x)) / boost::tuples::length<Dists>::value;
}
