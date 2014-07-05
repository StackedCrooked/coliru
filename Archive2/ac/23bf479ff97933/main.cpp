#include <algorithm>    // sort
#include <cmath>        // abs, atan, max
#include <iostream>     // cout
#include <tuple>        // forward_as_tuple
#include <vector>       // vector

struct Point
{
    int x, y;    
    
    int radius() const
    {
        // block-wise radius, use Pythagoras for ring-wise radius
        return std::max(std::abs(x), std::abs(y));
    }
    
    double angle() const
    {
        // result of atan2 in [-pi, +pi]
        auto a = std::atan2(y, x);
        
        // we want result in [0, 2 pi]
        if (a < 0)             
            a += 8 * std::atan(1); // add 2 pi
        return a;
    }
    
    friend bool operator<(Point const& L, Point const& R)
    {
        // delegate to operator< of std::tuple
        return 
            std::forward_as_tuple(L.radius(), L.angle()) < 
            std::forward_as_tuple(R.radius(), R.angle())
        ;
    }
    
    friend std::ostream& operator<<(std::ostream& os, Point const& p)
    {
        return os << "{" << p.x << ", " << p.y << "}"; 
    }
};

int main() 
{    
    auto points = std::vector<Point> { 
        {-1, 1}, { 0, 1}, { 1, 1}, 
        {-1, 0}, { 0, 0}, { 1, 0}, 
        {-1,-1}, { 0,-1}, { 1,-1} 
    };
    
    // sort will use std::less<Point> which finds operator<(Point, Point)
    std::sort(begin(points), end(points));
    
    for (auto&& p : points)
        std::cout << p << ",";
    std::cout << "\n";
}

    
