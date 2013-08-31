#include <functional>
#include <iostream>

struct Point
{
    Point() = default;
    Point(unsigned x, unsigned y) : x(x), y(y) {}
    
    unsigned x, y;
};


static_assert(std::is_pod<Point>::value, "");


int main()
{
    std::array<char, 1024 * 1024> a;
    for (unsigned i = 0; i != a.size(); ++i)
    {
        a[i] = 0xFF;
    }
    
    // prevent optmization?
    std::cout << a[0] << ", " << a[1024 * 1024 - 1] << std::endl;
    
    
    std::cout << Point().x << std::endl;
    std::cout << Point().x << std::endl;
    std::cout << Point().x << std::endl;
    std::cout << Point().x << std::endl;
    std::cout << Point().x << std::endl;
    std::cout << Point().x << std::endl;
    
}