#include <boost/geometry.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/index/rtree.hpp>

namespace bg  = boost::geometry;
namespace bgi = bg::index;
namespace bgm = bg::model;

typedef bgm::point<float, 2, bg::cs::spherical_equatorial<bg::degree> > Point;
typedef bgm::box<Point> Box;
typedef std::pair<Box, int> BoxIdPair;

int main() {
    using Tree = bgi::rtree<BoxIdPair, bgi::rstar<16> >;
    Tree tree;

    BoxIdPair b1({ Point(24,  19), Point(35,  26) }, 100);
    tree.remove(b1);
}
