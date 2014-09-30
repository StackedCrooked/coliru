#include <iostream> 
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/geometries/register/point.hpp>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>

using namespace boost::geometry;

struct CustomPoint{
    double X;
    double Y;
};

namespace {
    template<typename T>
        struct shared_instancing : boost::shared_ptr<T> {
            using boost::shared_ptr<T>::shared_ptr;

            shared_instancing(boost::shared_ptr<T> sp = boost::make_shared<T>()) 
                : boost::shared_ptr<T>(sp)
            { }
        };
}

using cpPtr = shared_instancing<CustomPoint>; // boost::shared_ptr<CustomPoint>;

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
    typedef boost::geometry::model::polygon<cpPtr> polygon;

    polygon green, blue;

    boost::geometry::read_wkt(
        "POLYGON((2 1.3,2.4 1.7,2.8 1.8,3.4 1.2,3.7 1.6,3.4 2,4.1 3,5.3 2.6,5.4 1.2,4.9 0.8,2.9 0.7,2 1.3)"
            "(4.0 2.0, 4.2 1.4, 4.8 1.9, 4.4 2.2, 4.0 2.0))", green);

    boost::geometry::read_wkt(
        "POLYGON((4.0 -0.5 , 3.5 1.0 , 2.0 1.5 , 3.5 2.0 , 4.0 3.5 , 4.5 2.0 , 6.0 1.5 , 4.5 1.0 , 4.0 -0.5))", blue);

    std::vector<polygon> output;
    boost::geometry::union_(green, blue, output);

    int i = 0;
    std::cout << "green || blue:" << std::endl;
    for(polygon const& p: output)
    {
        std::cout << i++ << ": " << boost::geometry::area(p) << std::endl;
    }
}
