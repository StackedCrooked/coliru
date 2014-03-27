#include <boost/bind.hpp>
#include <boost/math/distributions.hpp>
#include <boost/variant.hpp>
#include <iostream>
#include <limits>
#include <vector>

template <typename T>
using VarDist = boost::variant<
    boost::math::normal_distribution<T>,
    boost::math::students_t_distribution<T>
    >;

namespace detail
{
    template <typename T> struct var_cdf_visitor : boost::static_visitor<T> {
        template <typename Dist>
            T operator()(Dist& dist, T& x) const { return boost::math::cdf(dist, x); }
    };
}

template<class T> T var_cdf(VarDist<T> a, T &x) {
    return boost::apply_visitor(boost::bind(detail::var_cdf_visitor<T>(), ::_1, boost::ref(x)), a);
}

int main (int, char*[])
{
    //get distribution objects
    boost::math::normal_distribution<double> s;
    boost::math::students_t_distribution<double> t(1);

    //use any to put just any kind of objects in one vector 
    typedef std::vector<VarDist<double> > Vec;
    Vec vec_any;
    vec_any.push_back(s);
    vec_any.push_back(t);

    //evaluation point and return value 
    double y;
    double x = 1.96;

    for (Vec::const_iterator iter = vec_any.begin(); iter != vec_any.end(); ++iter) {
        y = var_cdf(*iter,x);
        std::cout << y << std::endl;
    }
}
