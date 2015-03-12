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

std::vector<A> f()
{
    std::cout << "f()" << std::endl;
    std::vector<A> v;
    v.emplace_back(1);
    v.emplace_back(2);
    return v;
}

int main()
{
    
    auto va = f();
    return 0;
}
