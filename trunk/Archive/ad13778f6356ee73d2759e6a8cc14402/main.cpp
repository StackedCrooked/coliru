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
    Point() : x(), y() { std::cout << "default constructor" << std::endl; }
    Point(int x, int y) : x(x), y(y) { std::cout << "user constructor" << std::endl; }
    
    Point(const Point& p) : x(p.x), y(p.y) { std::cout << "copy" << std::endl; }
    Point& operator=(const Point & rhs) { x = rhs.x; y = rhs.y; std::cout << "copy assignment" << std::endl; return *this; }
    
    Point(Point&& p) : x(p.x), y(p.y) { std::cout << "move" << std::endl; }
    Point& operator=(Point && rhs) { x = rhs.x; y = rhs.y; std::cout << "move assignment" << std::endl; return *this; }

    int x, y;
};

int main()
{
    std::shared_ptr<Point> movable = share(Point(1, 2));
    std::cout << movable->x << ", " << movable->y << std::endl;
}
