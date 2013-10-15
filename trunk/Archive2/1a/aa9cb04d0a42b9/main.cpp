#include <boost/geometry/geometry.hpp> 
#include <boost/geometry/geometries/register/point.hpp> 
#include <boost/geometry/geometries/register/ring.hpp> 

struct MyPoint {
    double x, y/*, z*/;
};

BOOST_GEOMETRY_REGISTER_POINT_2D(MyPoint, double, boost::geometry::cs::cartesian, x, y/*, z*/)

typedef boost::geometry::model::polygon<MyPoint> Polygon;
BOOST_GEOMETRY_REGISTER_RING(Polygon::ring_type)

int main()
{
    using boost::geometry::append;
    using boost::geometry::correct;
    using boost::geometry::dsv;

    Polygon poly1;
    Polygon poly2;

    append(poly1, MyPoint {2, 0});
    append(poly1, MyPoint {2, 2});
    append(poly1, MyPoint {0, 2});
    append(poly1, MyPoint {0, 0});
    append(poly1, MyPoint {2, 0});

    append(poly2, MyPoint {3, 0});
    append(poly2, MyPoint {3, 3});
    append(poly2, MyPoint {0, 3});
    append(poly2, MyPoint {0, 0});
    append(poly2, MyPoint {3, 0});

    correct(poly1);
    correct(poly2);

    std::vector<Polygon> polys;
    if (boost::geometry::intersection(poly1, poly2, polys))
    {
        for (Polygon const& inter : polys)
            std::cout << "Intersection polygon area is " << boost::geometry::area(inter) << " with " << dsv(inter) << "\n";
    }
}
