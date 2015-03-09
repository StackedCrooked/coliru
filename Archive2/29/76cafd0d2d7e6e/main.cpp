#include <iostream>
#include <utility>
#include <vector>
struct A1
{
    A1(int a, int b){std::cout << a << "\t" << b;}
    
};

struct A2
{
    A2(std::pair<int,int>& p){std::cout << p.first << "\t" << p.second;}
};

template <typename T>
struct D : T
{
template<typename ...Args>
D(Args&& ...args) : T(std::forward<Args>(args)...){}
};

int main()
{
    D<A1> d1(1,1);
    std::cout << "done";
}
