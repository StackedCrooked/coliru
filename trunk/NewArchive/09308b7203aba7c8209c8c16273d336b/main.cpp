#include <iostream>
#include <memory>


/**
 * Intellisense-friendly alternative to make_shared.
 * 
 * For example: make_shared<T>(args...)
 * becomes:     share(T(args...))
 * 
 * Requires T to be movable.
 */
template<typename T>
std::shared_ptr<T> share(T && obj)
{
    return std::make_shared<T>(std::forward<T>(obj));
}


struct Point
{
    Point() : x(), y() {}
    Point(int x, int y) : x(x), y(y) {}
    
    Point(const Point&) = delete;
    Point& operator=(const Point&) = delete;
    
    Point(Point&&) = default;
    Point& operator=(Point&&) = default;

    int x, y;
};

int main()
{
    std::shared_ptr<Point> movable = share(Point(1, 2));
    std::cout << movable->x << ", " << movable->y << std::endl;
}
