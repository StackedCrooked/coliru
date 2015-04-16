#include <stdio.h>
#include <unordered_map>

struct Point
{
    int x, y;
    explicit Point(int initX, int initY): x(initX), y(initY) { }
    
    friend bool operator==(const Point &a, const Point &b)
    {
        return a.x == b.x && a.y == b.y;
    }
};

auto hashPoint = [](const Point &p) { return (size_t)(p.x ^ p.y); };

typedef std::unordered_map<Point, int, size_t(*)(const Point&)> PointMap;

int main(void)
{
    PointMap points(10, hashPoint); // <-- error is on this line
    points[Point(1, 2)] = 3;
    points[Point(4, 5)] = 6;
    
    for (const auto &entry: points)
        printf("(%d, %d) -> %d\n", entry.first.x, entry.first.y, entry.second);
    return 0;
}