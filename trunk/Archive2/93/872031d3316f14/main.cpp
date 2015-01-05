#include <boost/geometry.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/index/predicates.hpp>
#include <boost/geometry/index/rtree.hpp>
#include <boost/geometry/io/io.hpp>

namespace bg  = boost::geometry;
namespace bgi = boost::geometry::index;
using boost::make_iterator_range;
using point   = bg::model::d2::point_xy<int>;
using box     = bg::model::box<point>;

static auto boxof = [] (point p) { return box { p, p }; };

int main() {
    using Value = std::pair<box, int>;
    using Tree  = bgi::rtree<Value, bgi::rstar<32> >;

    Tree idx;

    std::vector<point> const points { point {1,10}, point {2,5}, point {5,8}, point {1,2}, point {8,10}, };

    for (size_t i = 0; i < points.size(); ++i)
        idx.insert(Value { boxof(points[i]), i });

    for (auto& entry : make_iterator_range(qbegin(idx, bgi::nearest(point{0,0}, 100)), {}))
        std::cout << bg::dsv(points[entry.second]) << " ";
}
