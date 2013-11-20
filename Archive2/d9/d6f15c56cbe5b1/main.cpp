#include <iostream>
#include <string>
#include <vector>

struct A
{
    int a;
    int b;
    char d;
};
struct B
{
    int a[2];
    char d;
};
template <typename OUT,typename IN>
OUT& cowboyCast(IN& a)
{
    return *((OUT*)(&a));
}
int main()
{
    A a;
    a.b=10;
    
    std::cout << cowboyCast<B>(a).a[1] << std::endl;
}
