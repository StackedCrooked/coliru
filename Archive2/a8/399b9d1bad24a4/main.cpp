#include <iostream>

struct Point
{
    double x, y;
};

Point midpoint(const Point& a, const Point& b)
{
    return { (a.x + b.x) / 2, (a.y + b.y) / 2 };
}

int main()
{
    Point mid = midpoint({0, 0}, {2, 4});
    std::cout << mid.x << " " << mid.y << std::endl;
    
    return 0;
}