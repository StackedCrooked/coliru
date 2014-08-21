#include <iostream>

class Point { 
public:
    constexpr Point() = default;

    constexpr Point(double xVal, double yVal) noexcept 
    : x(xVal), y(yVal) 
    {} 
    
    constexpr double xValue() const noexcept { return x; } 
    constexpr double yValue() const noexcept { return y; } 
    
    constexpr Point& setX(double newX) noexcept { x = newX; return *this; } 
    constexpr Point& setY(double newY) noexcept { y = newY; return *this; } 
    
private: 
    double x = {}, y = {}; 
}; 

int main() 
{
    constexpr auto p1 = Point();            // {0,0}
    constexpr auto p2 = Point(1, 1);        // {1,1}
    constexpr auto p3 = Point().setX(3);    // {3,0}
    
    std::cout << "{" << p1.xValue() << "," << p1.yValue() << "},";
    std::cout << "{" << p2.xValue() << "," << p2.yValue() << "},";
    std::cout << "{" << p3.xValue() << "," << p3.yValue() << "},";
}
