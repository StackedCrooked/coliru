#include <iostream>
#include <mutex>


// Thread-safe wrapper for an object of type T.
// Provides access via functor or pointer-to-member-function.
template<typename T>
struct Synchronized
{
    template<typename F, typename ...Args>
    auto apply(F f, Args&& ...args) const -> decltype(std::bind(f, std::declval<const T&>(), std::forward<Args>(args)...)())
    {
        std::lock_guard<std::mutex> lock(mMutex);
        return std::bind(f, std::ref(t), std::forward<Args>(args)...)();
    }
    
    template<typename F, typename ...Args>
    auto apply(F f, Args&& ...args)  -> decltype(std::bind(f, std::declval<T&>(), std::forward<Args>(args)...)())
    {
        std::lock_guard<std::mutex> lock(mMutex);
        return std::bind(f, std::ref(t), std::forward<Args>(args)...)();
    }

private:
    mutable std::mutex mMutex;
    T t;
};


struct Point
{
    void set(int x, int y) { this->x = x; this->y = y; }
    
    void move(int dx, int dy)
    {
        x += dx;
        y += dy;
    }
    
    void get(int& x, int& y) { x = this->x; y = this->y; }
    
    void print() const
    {
        std::cout << "x=" << x << " y=" << y << '\n';
    }
    
    int x, y;
};


int main()
{
    Synchronized<Point> point;
    
    point.apply([&](Point& p) { p.x = 1; p.y = 2; });
    point.apply([&](Point& p) { p.print(); });
    
    point.apply(&Point::set, 3, 4);    
    point.apply(&Point::print);
    
    point.apply(&Point::move, 1, -1);
    point.apply(&Point::print);
    
    
    int x = 0, y = 0;
    point.apply(&Point::get, std::ref(x), std::ref(y));
    std::cout << "x=" << x << " y=" << y << std::endl;
}
