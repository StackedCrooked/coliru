#include <iostream>
#include <vector>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/io/wkt/wkt.hpp>

#include <boost/foreach.hpp>

int main()
{
    typedef boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double> > polygon;
    using boost::geometry::correct;
    using boost::geometry::dsv;

    polygon green, blue;

    boost::geometry::read_wkt(
            "POLYGON((440820.110024126 4047009.80267429, 440806.545727707 4046942.39533656, 440797.171880196 4046895.8425726, 440804.202135392 4046888.73092639, 440813.573458131 4046935.27114371, 440827.140279322 4047002.69102807))", 
            green);
    boost::geometry::read_wkt(
            "POLYGON((440855.857887967 4046932.1248641, 440813.740724389 4046942.21109839, 440806.376538684 4046935.44583646, 440848.493702262 4046925.35960217))", 
            blue);

    correct(green);
    correct(blue);

    std::vector<polygon> output;
    boost::geometry::union_(green, blue, output);

    int i = 0;
    BOOST_FOREACH(polygon const& p, output)
    {
        std::cout << i++ << ": " << boost::geometry::area(p) << "\n";
        std::cout << "Shape: " << dsv(p) << "\n";
    }
}
