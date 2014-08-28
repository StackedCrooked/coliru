#include <vector>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp> 
#include <boost/geometry/geometries/segment.hpp>
#include <boost/geometry/algorithms/intersection.hpp>

#include <boost/multiprecision/gmp.hpp>
#include <boost/multiprecision/number.hpp>

namespace bg = boost::geometry;
namespace bm = boost::multiprecision;

typedef bm::number<bm::gmp_rational, bm::et_off> my_rational;
typedef bg::model::d2::point_xy<my_rational > point;
typedef boost::geometry::model::segment<point> segment;

int main(void)
{
    point a(0,0);
    point b(1,0);
    point c(1,1);
    point d(0,1);

    segment s1(a,c);
    segment s2(b,d);

    std::vector<point> ip;
    bg::intersection(s1, s2, ip); // Doesn't compile

    return 0;
}
