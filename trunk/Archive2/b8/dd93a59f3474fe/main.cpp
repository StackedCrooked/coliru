#include <iostream>
#include <vector>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/io/wkt/wkt.hpp>
#include <boost/foreach.hpp>

int main() {
    typedef boost::geometry::model::d2::point_xy<double> point;
    typedef boost::geometry::model::polygon<point> polygon;
    char const *poly1 = "POLYGON((45.4602851 9.1146293,45.4602851 9.1196293,45.4652851 9.1196293,45.4652851 9.1146293,45.4602851 9.1146293))";
    polygon poly, newPoly;

    boost::geometry::read_wkt(poly1, poly);
    boost::geometry::correct(poly);

    BOOST_FOREACH(point const & p, boost::geometry::exterior_ring(poly)) {
        boost::geometry::append(boost::geometry::exterior_ring(newPoly), p);
    }

    std::cout << std::setprecision(12) << boost::geometry::wkt(newPoly);
}
