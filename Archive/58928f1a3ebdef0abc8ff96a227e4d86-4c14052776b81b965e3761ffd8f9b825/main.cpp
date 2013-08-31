#include <vector>
#include <utility>
#include <iostream>
#include <functional>

using namespace std;

namespace Geom{
    
    struct Point{
        Point(double x_) : x(x_){}
        double x;
    };
};

namespace Geom{
    
    bool operator==(const Point& lhs, const Point& rhs){
        return (lhs.x == rhs.x);
    }
    
    bool operator!=(const Point& lhs, const Point& rhs){
        return !(lhs == rhs);
    }
};

int main( int argc, const char *argv[] )
{
    Geom::Point p1(1);
    Geom::Point p2(2);
    
    if( Geom::operator!=(p1, p2) )
        cout << "brutto" << endl;
    
    using namespace Geom;
    if( 1. != p1 )
        cout << "diversi" << endl;
    else
        cout << "uguali" << endl;
    double* a = NULL;
    //...
    if( NULL = a );
    
    
    return 0;
}
