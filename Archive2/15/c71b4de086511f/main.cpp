#include <boost/function_output_iterator.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/index/rtree.hpp>

namespace bgi = boost::geometry::index;
using point = boost::geometry::model::d2::point_xy<int, boost::geometry::cs::cartesian>;
using box = boost::geometry::model::box<point>;

int main()
{
    using Tree = bgi::rtree<box, bgi::rstar<32> >;
    Tree tree;

    size_t cardinality = 0; // number of matches in set
    auto count_only = boost::make_function_output_iterator([&cardinality] (Tree::value_type const&) { ++cardinality; });

    box query_box;
    tree.query(bgi::intersects(query_box), count_only);

    int nbElements = cardinality;
    return nbElements;
}
