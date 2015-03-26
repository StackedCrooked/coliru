#include <iostream>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point.hpp>
namespace bg = boost::geometry;
using Point = bg::model::point<double, 3, bg::cs::cartesian>;
using namespace bg;
using namespace std;

template<typename Point>
Point operator*(const Point & p, typename detail::param< Point >::type value) {
    cout << "Multiply point" << endl;
    Point result{p};
    multiply_value(result, value);
    return result;
}

template<typename Point1, typename Point2>
Point operator*(const Point1 & p1, const Point2 & p2) {
    cout << "Multiply point" << endl;
    Point result{p1};
    multiply_point(result, p2);
    return result;
}

int main()
{
    Point point1{1.0, 2.0, -1};
    Point point2{5.0, 1.0, -1.0};
    double value{2.0};

    // This code voluntarily does not compile, to prove that those two
    // operators are ambiguous, and that it is not possible to define
    // the `operator*` for both `multiply_value` AND `multiply_point`

    // Note that this works:
    point1 * point2;

    // But not this:
    point1 * value;
}
