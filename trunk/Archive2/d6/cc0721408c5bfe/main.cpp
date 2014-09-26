#include <algorithm>
#include <iostream>
#include <vector>

struct Tmp
{
    Tmp(int p)
        : v(p)
    {}
    Tmp(const Tmp& other)
        : v(other.v)
    {
        std::cout << "Tmp::Tmp(const Tmp& other)" << std::endl;
    }
    int v;
};

int main()
{
    std::vector<Tmp> v{1,2,3,4,5};
    auto p = std::min_element(begin(v), end(v), [] (const Tmp& a, const Tmp& b) { return a.v < b.v; });
    std::cout << p->v << std::endl;
}