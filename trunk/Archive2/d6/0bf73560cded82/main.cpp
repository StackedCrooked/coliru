#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/box.hpp>

#include <boost/geometry/index/rtree.hpp>

// to store queries results
#include <vector>

// just for output
#include <iostream>
#include <boost/foreach.hpp>

namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;

template <typename Point>
struct predicate 
{
    predicate(const Point& point_,unsigned distance_):point(point_),distance(distance_){}
    
    template <typename Value>
    bool operator()(const Value& value) const
    {
        return bg::distance(point,value.first) < distance;
    }
    
    Point point;
    unsigned distance;
};

int main(void)
{
    typedef bg::model::point<float, 2, bg::cs::cartesian> point;
    typedef std::pair<point, unsigned> value;

    // create the rtree using default constructor
    bgi::rtree< value, bgi::quadratic<16> > rtree;

    // create some values
    for ( unsigned i = 0 ; i < 10 ; ++i )
    {
        // create a box
        point p(i, i);
        // insert new value
        rtree.insert(std::make_pair(p, i));
    }

    // find values nearer than a set distance
    predicate<point> pred1(point(0,0),3);
    std::vector<value> result_1;
    rtree.query(bgi::satisfies(pred1),std::back_inserter(result_1));
    
    predicate<point> pred2(point(5,5),2);
    std::vector<value> result_2;
    rtree.query(bgi::satisfies(pred2),std::back_inserter(result_2));

    // display results
    std::cout << "distance < 3 from ";
    std::cout << bg::wkt<point>(point(0,0)) << std::endl;
    std::cout << "distance query result:" << std::endl;
    BOOST_FOREACH(value const& v, result_1)
        std::cout << bg::wkt<point>(v.first) << " - " << v.second << std::endl;

    std::cout << "distance < 2 from ";
    std::cout << bg::wkt<point>(point(5,5)) << std::endl;
    std::cout << "distance query result:" << std::endl;
    BOOST_FOREACH(value const& v, result_2)
        std::cout << bg::wkt<point>(v.first) << " - " << v.second << std::endl;

    return 0;
}