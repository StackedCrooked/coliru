#include <boost/math/distributions.hpp>

#include <boost/tuple/tuple.hpp>
#include <boost/fusion/adapted/boost_tuple.hpp>
#include <boost/fusion/algorithm.hpp>
#include <boost/phoenix.hpp>
#include <boost/phoenix/function.hpp>

#include <iostream>

namespace bm = boost::math;
using namespace boost::phoenix::arg_names;

template <typename Dist, typename T>
T apply_dist(Dist const& dist, T const& x) {
    return boost::math::cdf(dist, x); 
}

BOOST_PHOENIX_ADAPT_FUNCTION(double, apply_dist_, apply_dist, 2)

int main()
{
    double x = 1.96;

    boost::fusion::for_each(
            boost::make_tuple(bm::normal(), bm::students_t(1)),
            std::cout << apply_dist_(arg1, x) << "\n"
            );
}
