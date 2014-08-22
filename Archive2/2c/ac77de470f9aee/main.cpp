#include <vector>
#include <unordered_set>
#include <functional>

struct Point
{
    float x;
    float y;
    Point() : x(0), y(0) {}
};

int main()
{
    auto hash=[](const Point& pt){
        return (size_t)(pt.x*100 + pt.y);
    };
    auto equal=[](const Point& pt1, const Point& pt2){
        return ((pt1.x == pt2.x) && (pt1.y == pt2.y));
    };
    using PointHash=std::unordered_set<Point,decltype(hash),decltype(equal)>;
//equalKey()(Point(),Point());//ok
    PointHash Test(10,hash,equal);

    return 0;
}
