#include <boost/bind.hpp>
#include <boost/math/distributions.hpp>
#include <boost/variant.hpp>
#include <iostream>
#include <limits>
#include <vector>

namespace detail
{
    template <typename T> struct var_cdf_visitor : boost::static_visitor<T> {
        template <typename Dist>
            T operator()(Dist const& dist, T const& x) const { return boost::math::cdf(dist, x); }
    };
}

template<class T, typename... Dist> T var_cdf(boost::variant<Dist...> const& a, T const& x) {
    return boost::apply_visitor(boost::bind(detail::var_cdf_visitor<T>(), ::_1, x), a);
}

int main()
{
    namespace bm = boost::math;
    typedef std::vector<boost::variant<bm::normal, bm::students_t> > Vec;

    Vec vec { bm::normal(), bm::students_t(1) };

    //evaluation point and return value 
    double x = 1.96;

    for (auto& dist : vec)
        std::cout << var_cdf(dist,x) << std::endl;
}
