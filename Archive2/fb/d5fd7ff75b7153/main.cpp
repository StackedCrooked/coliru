#include <iostream>
#include <vector>

struct A
{
    A(int j) : i(j)
    {
        std::cout << "A("<< i << ")" << std::endl;
    }
    A(const A& a) : i(a.i)
    {
        std::cout << "A(const A& "<< i << ")" << std::endl;
    }
    ~A()
    {
        std::cout << "~A("<<i<<")" << std::endl;
    }
    int i;
};



int main()
{
    std::vector<A> v;
    v.reserve(2);
    v.emplace_back(1);
    v.emplace_back(2);
    auto w = v;
    return 0;
}
