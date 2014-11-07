#include <iostream>
#include <list>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>


int main()
{
    typedef boost::geometry::model::d2::point_xy<double> point_type;
    typedef boost::geometry::model::polygon<point_type> polygon_type;

    polygon_type poly;
    poly.outer().assign({
        point_type {     2,   1.3   },
        point_type {   2.4,   1.7   },
        point_type {   2.8,   1.8   },
        point_type {   3.4,   1.2   },
        point_type {   3.7,   1.6   },
        point_type {   3.4,     2   },
        point_type {   4.1,     3   },
        point_type {   5.3,   2.6   },
        point_type {   5.4,   1.2   },
        point_type {   4.9,   0.8   },
        point_type {   2.9,   0.7   },
        point_type {     2,   1.3   },
    });

    poly.inners().emplace_back();
    poly.inners().back().assign({
        {   4.0,   2.0   },
        {   4.2,   1.4   },
        {   4.8,   1.9   },
        {   4.4,   2.2   },
        {   4.0,   2.0   },
    });

    point_type p(4, 1);

    std::cout << "within: " << (boost::geometry::within(p, poly) ? "yes" : "no") << std::endl;

    return 0;
}
