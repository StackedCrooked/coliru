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
    auto hashFunc=[&hash](){
        return  std::function<size_t(const Point&)> (hash);
    };
    auto equal=[](const Point& pt1, const Point& pt2){
        return ((pt1.x == pt2.x) && (pt1.y == pt2.y));
    };
    auto equalFunc=[&equal](){
        return std::function<size_t(const Point&,const Point&)> (equal);
    };
    using PointHash=std::unordered_set<Point,decltype(hashFunc),decltype(equalFunc)>;
//equalKey()(Point(),Point());//ok
    PointHash Test(10,hashFunc,equalFunc);

    return 0;
}
