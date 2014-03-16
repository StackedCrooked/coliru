#include <iostream>
#include <vector>
#include <math.h>
#include <boost/shared_ptr.hpp>

struct Point3D{
    double x;
    double y;
    double z;
};

class Point{
    public:
    operator Point3D() const {
        double x = 1.;
        Point3D res = {x, 2, 3};
        return res;
    }
};

int main(){
    const Point p;
    
    Point3D p3 = p;
    p3.x = 5;
    
    return 0;
}
