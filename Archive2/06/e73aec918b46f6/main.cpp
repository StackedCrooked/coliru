#include <iostream>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point.hpp>
namespace bg = boost::geometry;
using Point = bg::model::point<double, 3, bg::cs::cartesian>;
using namespace bg;
using namespace std;

// For multiplying value * point
template<typename Point>
Point operator*(typename detail::param< Point >::type value, const Point & p) {
    Point result{p};
    cout << "Multiply value * point" << endl;
    multiply_value(result, value);
    return result;
}

/*

// If this operator is added, NEITHER `point * value` NOR `value * point`
// multiplication can work

// For multiplying point * value
template<typename Point>
Point operator*(const Point & p, typename detail::param< Point >::type value) {
    Point result{p};
    cout << "Multiply point * value" << endl;
    multiply_value(result, value);
    return result;
}

*/

int main()
{
    Point point1{1.0, 2.0, -1};
    Point point2{5.0, 1.0, -1.0};
    double value{2.0};

    // This code voluntarily does not compile, to prove that the
    // order of the operation in the operator must be chosen,

    // Note that this works:
    value * point1;

    // But this does not:
    point1 * value;
}
