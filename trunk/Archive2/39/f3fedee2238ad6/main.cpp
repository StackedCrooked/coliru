#include <vector>
#include <unordered_set>
#include <functional>
#include <iostream>

struct Point {
    float x;
    float y;
};

int main() {
    auto hash = [](const Point& pt){ return (size_t)(pt.x*100 + pt.y); };

    auto equal = [](const Point& pt1, const Point& pt2){ return ((pt1.x == pt2.x) && (pt1.y == pt2.y)); };

    using PointHash=std::unordered_set<Point,decltype(hash),decltype(equal)>;
    PointHash Test(10,hash,equal);
    
    Test.insert(Point{1.0f, 2.0f});
    Test.insert(Point{3.0f, 4.0f});
    
    for(auto i : Test) std::cout << i.x << ", " << i.y << std::endl;

    return 0;
}
