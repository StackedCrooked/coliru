#include <iostream>

class Point { 
public:
    constexpr Point(double xVal, double yVal) noexcept 
    : x(xVal), y(yVal) 
    {} 
    
    constexpr double xValue() const noexcept { return x; } 
    constexpr double yValue() const noexcept { return y; } 
    
    constexpr void setX(double newX) noexcept { x = newX; } 
    constexpr void setY(double newY) noexcept { y = newY; } 
    
private: 
    double x, y; 
}; 

constexpr Point project_x(Point const& p) 
{ auto nrv(p); nrv.setX(0); return nrv; }

int main() 
{
    constexpr auto p = Point(1, 1);     // {1,1}
    constexpr auto y = project_x(p);    // {0, 1} 
    
    std::cout << "{" << p.xValue() << "," << y.yValue() << "},";
    std::cout << "{" << y.xValue() << "," << y.yValue() << "},";
}
