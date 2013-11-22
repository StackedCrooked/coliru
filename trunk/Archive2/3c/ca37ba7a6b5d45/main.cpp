#include <cmath>
#include <vector>
#include <list>
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
    Point() : m_x(0), m_y(0) {}
};

struct Path
{
    list<Point> m_steps;

    void print_step (const Point& pt);
    void print_path ();    
};


void Path::print_step (const Point& pt) { 
    cout  << "[" << pt.m_x << "," << pt.m_y << "]\n"; 
}

void Path::print_path()
{
    // change the following code to get the same result:
    // from here ....
    
    for( list<Point>::iterator it_step = m_steps.begin(); it_step != m_steps.end(); ++it_step )
    {
        print_step( *it_step );
    }
    
    // ... to here
}


int main()
{
    Path path;
    path.m_steps.push_back( Point(10, 10) );
    path.m_steps.push_back( Point( 0, 10) );
    path.m_steps.push_back( Point(10,  0) );

    
    cout << "Path is:\n";
    path.print_path();
}