#include <algorithm>
#include <iostream>
#include <vector>

template <typename T>
struct SquareFunc
{
    void operator()(T& t) { t = t * t; }
};

int main()
{
    std::vector<int> v1 = { 1, 2, 3 };
    std::vector<float> v2 { 1.0f, 2.0f, 3.0f };
    
    std::for_each(v1.begin(), v1.end(), SquareFunc<int>());
    std::for_each(v2.begin(), v2.end(), SquareFunc<float>());
    
    return 0;
}