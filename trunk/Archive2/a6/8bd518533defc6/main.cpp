#include <boost/geometry/geometries/register/point.hpp>
#include <boost/geometry/geometries/register/ring.hpp>
#include <boost/geometry/geometries/geometries.hpp> 
#include <boost/geometry/core/point_order.hpp> 
#include <boost/geometry.hpp>
#include <iostream>
#include <ostream>
#include <vector>

using namespace boost::geometry;
using namespace std;

struct Point { double x, y; };

BOOST_GEOMETRY_REGISTER_POINT_2D(Point , double, cs::cartesian, x, y)
BOOST_GEOMETRY_REGISTER_RING(vector<Point>)

namespace boost { namespace geometry
{
   template<>
   struct point_order<vector<Point>>
   {
      //static const order_selector value=counterclockwise;
      static const order_selector value=clockwise;
   };
}}

template<typename Ring>
void print(const Ring &r)
{
   for(auto p : r)
      cout << "(" << p.x << "," << p.y << ")";
   cout << endl;
}

int main()
{
   std::vector<Point> ring{{0.0,0.0},{1.0,0.0},{0.0,1.0},{0.0,0.0}};
   print(ring);
   correct(ring);
   print(ring);
}
