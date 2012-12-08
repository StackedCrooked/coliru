#include <iostream>
#include <memory>


struct Point
{
    Point() : x(), y() {}
    Point(int x, int y) : x(x), y(y) {}

    int x, y;
};


// share(T(args...)) should return the same as make_shared<T>(args...)
// requires T to be movable
template<typename T>
std::shared_ptr<T> share(T && obj)
{
    return std::make_shared<T>(std::forward(obj));
}


int main()
{
    std::shared_ptr<Point> point = share(Point(1, 2));
    std::cout << point->x << ", " << point->y << std::endl;
}