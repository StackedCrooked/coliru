#include <iostream>
#include <vector>
#include <boost/assign/std/vector.hpp>
#include <boost/geometry.hpp>
#include <boost/geometry/algorithms/area.hpp>
#include <boost/geometry/algorithms/assign.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/io/dsv/write.hpp>

int main()
{
    using namespace boost::assign;
    typedef boost::geometry::model::d2::point_xy<double> point_xy;
    
    // Create points to represent a 5x5 closed polygon.
    std::vector<point_xy> points;
    points +=
      point_xy(0,0),
      point_xy(0,5),
      point_xy(5,5),
      point_xy(5,0),
      point_xy(0,0)
      ;
    
    // Create a polgyon object and assign the points to it.
    boost::geometry::model::polygon<point_xy> polgyon;  
    boost::geometry::assign_points(polgyon, points);
    
    std::cout << "Polygon " << boost::geometry::dsv(polgyon) << 
      " has an area of " << boost::geometry::area(polgyon) << std::endl;
}
