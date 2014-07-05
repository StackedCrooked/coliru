#include <cmath>        // abs, atan, atan2, max
#include <iostream>     // cout
#include <map>          // map
#include <tuple>        // forward_as_tuple

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
    auto points = std::map<Point, int> { 
        {{-1, 1}, 4}, {{ 0, 1}, 3}, {{ 1, 1}, 2}, 
        {{-1, 0}, 5}, {{ 0, 0}, 0}, {{ 1, 0}, 1},
        {{-1,-1}, 6}, {{ 0,-1}, 7}, {{ 1,-1}, 8}
    };
    
    for (auto&& elem : points)
        std::cout << elem.second << ",";
    std::cout << "\n";
}

    
