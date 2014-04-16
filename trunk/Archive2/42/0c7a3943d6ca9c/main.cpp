#include <iostream>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/algorithms/assign.hpp>
namespace bg = boost::geometry;

template <std::size_t D, std::size_t N>
struct fill
{
    template <typename Point>
    static void apply(Point& p, typename bg::coordinate_type<Point>::type const& v)
    {
        bg::set<D>(p, v);
        fill<D + 1, N>::apply(p, v);
    }
};
template <std::size_t N>
struct fill<N, N>
{
    template <typename Point>
    static void apply(Point&, typename bg::coordinate_type<Point>::type const&) {}
};

int main()
{
   bg::model::point<double, 100, bg::cs::cartesian> p1;
   fill<0, 100>::apply(p1, 5);
   std::cout << "Done\n";
   return 0;
}