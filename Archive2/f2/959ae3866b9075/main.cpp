#include <iostream> 
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/register/point.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

using namespace boost::geometry;

class CustomPoint{
public:
    double X;
	double Y;
};

using cpPtr = boost::shared_ptr<CustomPoint>;

namespace boost { namespace geometry { namespace traits {
    BOOST_GEOMETRY_DETAIL_SPECIALIZE_POINT_TRAITS(cpPtr, 2, double, cs::cartesian)

    template<> struct access<cpPtr, 0> {
        static inline double get(cpPtr const& p) { return p->X; }
        static inline void set(cpPtr& p, double const& value) { p->X = value; }
    };
    template<> struct access<cpPtr, 1> {
        static inline double get(cpPtr const& p) { return p->Y; }
        static inline void set(cpPtr& p, double const& value) { p->Y = value; }
    };
}}}

int main()
{
	auto p1 = boost::make_shared<CustomPoint>();
	auto p2 = boost::make_shared<CustomPoint>();

	namespace bg = boost::geometry;

	bg::assign_values(p1, 1, 1);
	bg::assign_values(p2, 2, 2);

	double d = bg::distance(p1, p2);

	std::cout << "Distance: " << d << std::endl;

	return 0;
}