#include <iostream>
#include <mutex>


// Thread-safe wrapper for an object of type T.
// Provides access via functor or pointer-to-member-function.
template<typename T>
struct Synchronized
{
    // calls f(const T&)
    template<typename F>
    auto apply(F&& f) const -> decltype(f(std::declval<const T&>()))
    {
        std::lock_guard<std::mutex> lock(mMutex);
        f(t);
    }
    
    // calls f(T&)
    template<typename F>
    auto apply(F&& f) -> decltype(f(std::declval<T&>()))
    {
        std::lock_guard<std::mutex> lock(mMutex);
        f(t);
    }
    
    // applies member function
    template<typename PTMF, typename ...Args>
    auto apply(PTMF ptmf, Args&& ...args) -> decltype((std::declval<T>().*ptmf)(std::forward<Args>(args)...))
    {
        std::lock_guard<std::mutex> lock(mMutex);
        return (t.*ptmf)(std::forward<Args>(args)...);
    }
    
    // applies const member function
    template<typename PTMF, typename ...Args>
    auto apply(PTMF ptmf, Args&& ...args) const -> decltype((std::declval<T>().*ptmf)(std::forward<Args>(args)...))
    {
        std::lock_guard<std::mutex> lock(mMutex);
        return (t.*ptmf)(std::forward<Args>(args)...);
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
    point.apply(&Point::print);    
    
    point.apply(&Point::set, 3, 4);    
    point.apply(&Point::print);
    
    point.apply(&Point::move, 1, -1);
    point.apply(&Point::print);
}

