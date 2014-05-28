#include <boost/tuple/tuple.hpp>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/geometries/adapted/boost_tuple.hpp>
#include <boost/foreach.hpp>
typedef boost::geometry::model::polygon<boost::tuple<int, int> > Polygon;

BOOST_GEOMETRY_REGISTER_BOOST_TUPLE_CS(cs::cartesian)

void test_boost_intersection() {
    Polygon green, blue;
    boost::geometry::read_wkt("POLYGON((0 0,0 9,9 9,9 0,0 0))", green);
    boost::geometry::read_wkt("POLYGON((2 2,2 9,9 9,9 2,2 2))", blue);
    boost::geometry::correct(green);
    boost::geometry::correct(blue);
    std::deque<Polygon> output;
    boost::geometry::intersection(green, blue, output);
    BOOST_FOREACH(Polygon const& p, output)
    {
        std::cout << boost::geometry::dsv(p) << std::endl;
    }
}

int main()
{
    test_boost_intersection();
}
