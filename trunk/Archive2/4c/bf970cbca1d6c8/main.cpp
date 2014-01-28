#include <vector>

//Without templates
class Vector
{
    std::vector<double> baseArray;
    
public:
    Vector(int n): baseArray(n) {}
};

#include <array>

//With templates
template<int N>
class TemplatedVector
{
    std::array<double, N> baseArray;
    
public:
    TemplatedVector() {}
};

int main()
{
    Vector v(3);
    TemplatedVector<3> tv;
    
    return 0;
}