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


struct Movable
{
    Movable() : x(), y() {}
    Movable(int x, int y) : x(x), y(y) {}
    
    Movable(const Movable&) = delete;
    Movable& operator=(const Movable&) = delete;
    
    Movable(Movable&&) = default;
    Movable& operator=(Movable&&) = default;

    int x, y;
};

int main()
{
    std::shared_ptr<Movable> movable = share(Movable(1, 2));
    std::cout << movable->x << ", " << movable->y << std::endl;
}
