#include <boost/mpl/vector.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/joint_view.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/equal.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <type_traits>

typedef boost::mpl::vector<int, float> v1;
typedef boost::mpl::vector<double, long> v2;
typedef boost::mpl::joint_view<v1, v2> v3;

static_assert(boost::mpl::size<v3>::value == 4, "!");
static_assert(boost::mpl::equal<v3, boost::mpl::vector<int, float, double, long>>::value, "!1");

template<typename T>
struct W {
};

typedef boost::mpl::transform<v1, W<boost::mpl::placeholders::_1> > v1_t;
static_assert(std::is_same<boost::mpl::deref<boost::mpl::begin<v1_t>>::type, W<int>>::value, "!2");
static_assert(boost::mpl::equal<v1_t, boost::mpl::vector<W<int>, W<float>>>::value, "!3");

typedef boost::mpl::transform<v3, W<boost::mpl::placeholders::_1> > v3_t;

//static_assert(boost::mpl::size<v3_t>::value == 4, "!");
//static_assert(boost::mpl::equal<v3_t, boost::mpl::vector<W<int>, W<float>, W<double>, W<long>>>::value, "!");

int main()
{
    return 0;
}