#include <boost/polygon/polygon.hpp>

using namespace boost::polygon;
typedef polygon_90_with_holes_data<int> Polygon90;
typedef polygon_traits<Polygon90>::point_type MyPoint;

int main() {
    MyPoint const pts[] = { { 0, 0 }, { 0, 10 }, { 30, 10 }, { 30, 20 }, { 10, 20 }, { 10, 0 } };

    Polygon90 poly;
    set_points(poly, std::begin(pts), std::end(pts));

    std::vector<boost::polygon::rectangle_data<int> > rects;
    get_rectangles(rects, poly);
}
