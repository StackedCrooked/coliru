#include <iostream>
#include <string>
#include <sstream>
#include <utility>

namespace test
{
    
using std::to_string;

template <class T>
std::string to_string(const T& item)
{
    std::cout << "test::to_string" << std::endl;
    std::ostringstream ss;
    ss << item;
    return ss.str();
}

}

struct point
{
    int x, y;  
};

std::ostream& operator<<(std::ostream& os, const point& p)
{
    return os << "{ x = " << p.x << ", y = " << p.y << " }"; 
}

int main()
{
    point p = {2, 2};
    std::cout << test::to_string(p) << std::endl;
    std::cout << test::to_string(42) << std::endl;
}