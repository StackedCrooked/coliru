#include <iostream>
#include <utility> // std::make_pair
#include <boost/geometry.hpp>
#include <boost/geometry/algorithms/area.hpp>
#include <boost/geometry/algorithms/assign.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/io/dsv/write.hpp>
#include <boost/scoped_array.hpp>

int main()
{
    typedef boost::geometry::model::d2::point_xy<double> point_xy;

    // Create points to represent a 5x5 closed polygon.
    const std::size_t points_size = 6;
    boost::scoped_array<point_xy> points(new point_xy[points_size]);
    points[0] = point_xy(0,0);
    points[1] = point_xy(0,5);
    points[2] = point_xy(0,5);
    points[3] = point_xy(5,5);
    points[4] = point_xy(5,0);
    points[5] = point_xy(0,0);

    // Create a polygon object and assign the points to it.
    boost::geometry::model::polygon<point_xy> polygon;  
    boost::geometry::assign_points(
      polygon, 
      std::make_pair(&points[0], &points[0] + points_size));

    std::cout << "Polygon " << boost::geometry::dsv(polygon) << 
      " has an area of " << boost::geometry::area(polygon) << std::endl;
}