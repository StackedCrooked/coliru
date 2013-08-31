
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>

template<typename T, typename ... V>
void doVector(std::vector<T> v, V&&...value) 
{
    v.emplace_back(std::forward<V>(value)...);
}

struct point
{
    point(int, int) {}
};

int main()
{
    std::vector<int> v;
    int i=100;
    doVector(v, 10);
    doVector(v, i);
    
    std::vector<point> pts;
    doVector(pts, 1, 2);
}