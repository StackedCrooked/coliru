#include <iostream>
#include <memory>
 


class Point
{
    
    public:
    double *d_x;
    double *d_y;
    Point(double x=0.0, double y=0.0): 
    d_x(std::make_shared<double>(x)),
    d_y(std::make_shared<double>(y))
    { }
};
 
int main()
{
    Point pt(2.3,0.1);
    std::cout << *pt.d_x << " " << *pt.d_y << std::endl;
}