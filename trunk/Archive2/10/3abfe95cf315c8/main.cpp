#include <iostream>
#include <vector>
#include <boost/geometry.hpp>
#include <boost/geometry/strategies/cartesian/distance_pythagoras.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/geometries/linestring.hpp>
#include <boost/geometry/multi/geometries/multi_polygon.hpp>
#include <boost/geometry/io/wkt/wkt.hpp>
#include <boost/foreach.hpp>

int main()
{
    typedef boost::geometry::model::d2::point_xy<double> point;
    typedef boost::geometry::model::polygon<point> polygon;
    std::stringstream ss;
    std::string sstring;
    char const *poly1 =
        "POLYGON((45.4602851 9.1146293,45.4602851 9.1196293,45.4652851 9.1196293,45.4652851 9.1146293,45.4602851 9.1146293))";
    polygon poly, newPoly;
    point p1;

    boost::geometry::read_wkt(poly1, poly);
    boost::geometry::correct(poly);
    BOOST_FOREACH(point const & p, boost::geometry::exterior_ring(poly))
    {
        //     ss << boost::geometry::wkt(p);
        //      p1.x(p.y());
        //      p1.y(p.x());
        boost::geometry::append(boost::geometry::exterior_ring(newPoly), p);
    }
    std::cout << std::setprecision(12) << boost::geometry::wkt(newPoly);
}
