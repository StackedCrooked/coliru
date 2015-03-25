#include <boost/function_output_iterator.hpp>
#include <boost/phoenix.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/index/rtree.hpp>

namespace bgi = boost::geometry::index;
typedef boost::geometry::model::d2::point_xy<int, boost::geometry::cs::cartesian> point;
typedef boost::geometry::model::box<point> box;

int main()
{
    typedef bgi::rtree<box, bgi::rstar<32> > Tree;
    Tree tree;

    box query_box;
    auto r = boost::make_iterator_range(bgi::qbegin(tree, bgi::intersects(query_box)), bgi::qend(tree));

    size_t nbElements = boost::distance(r);

    return nbElements;
}
