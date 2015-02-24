#include <cmath>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <cassert>

using namespace std;
using namespace std::placeholders;


struct Point
{
    double m_x;
    double m_y;
    
    Point(double x, double y) : m_x(x), m_y(y) {}
    
    double length() const;
    void   move_by( const Point& offset );    
};


double Point::length() const {
    return sqrt(m_x*m_x + m_y*m_y);
}

void  Point::move_by( const Point& offset ) {
    m_x += offset.m_x;
    m_y += offset.m_y;
}

void print (const Point& pt) {
    std::cout  << "( " << pt.m_x << ", " << pt.m_y << " )\n";
}


int main()
{
    vector<Point> points;
    points.push_back( Point(10, 10) );
    points.push_back( Point( 0, 10) );
    points.push_back( Point(10,  0) );

    Point offset(5, 0);

    for_each (points.begin(), points.end(), bind(&Point::move_by, _1, offset));
    
    for_each (points.begin(), points.end(), print);


}