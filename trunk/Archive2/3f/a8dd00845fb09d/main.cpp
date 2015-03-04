#include <iostream>
#include <string>
#include <array>
#include <numeric>

template<typename T, std::size_t N>
class Point : public std::array<T,N>
{
public:
    template<typename... Args>
    Point(Args&&... args) : std::array<T,N>{{args...}} {}
    
    Point(Point&) = default;
    Point& operator=(const Point&) = default;

    static Point min(const Point&, const Point&) {
        return {};    
    }
};

Point<int, 5> p = {1, 2, 3, 4, 5};
std::array<int, 5> a = {1, 2, 3, 4, 5};

int main()
{
    Point<float,3> array[100] = {};
    Point<float,3> min = std::accumulate(array, array+100, array[0], Point<float,3>::min);
    return 0;
}