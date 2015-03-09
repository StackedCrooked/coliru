#include <iostream>
#include <utility>
#include <vector>
struct A1
{
    A1(int a, int b){}
};

struct A2
{
    A2(std::pair<int,int>& p){}
};

struct A3
{
    A3(std::vector<int>& v){}
};

template <typename T>
struct D : T
{
    
};

int main()
{
    D<A1> d1(1,1);
    std::cout << "done";
}
