#include <boost/geometry.hpp>
#include <boost/geometry/geometries/geometries.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <iostream>
#include <vector>

int main() {
    typedef boost::geometry::model::d2::point_xy<int16_t, boost::geometry::cs::cartesian> Point_t;
    typedef boost::geometry::model::polygon<Point_t> Polygon_t;
    typedef boost::geometry::model::multi_polygon<Polygon_t> MultiPolygon_t;

    std::vector<Point_t> points1;
    points1.push_back(Point_t(1473, 627));
    points1.push_back(Point_t(1473, 1155));
    points1.push_back(Point_t(908, 1155));
    points1.push_back(Point_t(908, 627));

    Polygon_t poly1;
    boost::geometry::assign_points(poly1, points1);
    boost::geometry::correct(poly1);

    MultiPolygon_t multiPoly;

    multiPoly.push_back(poly1);

    std::vector<Point_t> points2;
    points2.push_back(Point_t(1956, 956));
    points2.push_back(Point_t(1956, 1028));
    points2.push_back(Point_t(115, 1023));
    points2.push_back(Point_t(127, 951));

    Polygon_t poly2;
    boost::geometry::assign_points(poly2, points2);
    boost::geometry::correct(poly2);

    MultiPolygon_t resultMulti;
    MultiPolygon_t resultSimple;

    boost::geometry::difference(multiPoly, poly2, resultMulti);
    boost::geometry::difference(poly1, poly2, resultSimple);

    bool bMultiEmpty = resultMulti.empty();
    bool bSimpleEmpty = resultSimple.empty();

    assert(!bSimpleEmpty);
    assert(!bMultiEmpty);
}
