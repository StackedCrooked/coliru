#include <iostream>
#include <vector>
#include <string>
#include <boost/geometry.hpp>
#include <boost/geometry/io/io.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/index/distance_predicates.hpp>
#include <boost/geometry/index/predicates.hpp>
#include <boost/geometry/index/rtree.hpp>

namespace bg  = boost::geometry;
namespace bgi = bg::index;
namespace bgm = bg::model;

//typedef bgm::point<float, 2, bg::cs::spherical_equatorial<bg::degree> > Point;
typedef bgm::point<float, 2, bg::cs::cartesian> Point;
typedef bgm::box<Point> Box;
typedef std::pair<Box, int> BoxIdPair;

int main() {
    using Tree = bgi::rtree<BoxIdPair, bgi::rstar<16> >;
    Tree tree;

    // Some tree filling code excised from here for the sake of a minimal example.
    tree.insert({ { Point(24,  19), Point(35,  26) }, 100 });
    tree.insert({ { Point(41, 112), Point(54, 148) }, 150 });
    tree.insert({ { Point(34,  24), Point(36, 100) },  92 });
    tree.insert({ { Point(21,   8), Point(43,  15) },   8 });

    while (!tree.empty()) {
        std::cout << "Tree contains " << tree.size() << " box-id values." << std::endl;
        // 1. Choose arbitrary BoxIdPair to be the leader of a new canopy.
        //    Remove it from the tree. Insert it into the canopy map, with its
        //    corresponding id.
        Point origin(0.0, 0.0);

        auto first = bgi::qbegin(tree, bgi::nearest(origin, 1)), 
             last  = bgi::qend(tree);

        if (first != last)
        {
#if 0
            // 1. with an object
            tree.remove(*first); // assuming single result
#elif 1
            // 2. with a loop
            for(auto const& bip: boost::make_iterator_range(first, last))
            {
                std::cout << " box -> " << bg::dsv(bip.first) << " id  -> " << bip.second << "\n";
                tree.remove(bip);
            }
#elif 1
            // 3. with iterators
            tree.remove(first, last);
#elif 1
            // 4. with a range
            tree.remove(boost::make_iterator_range(first, last));
#endif
        }
    }
    std::cout << "Tree emptied\n";
}
