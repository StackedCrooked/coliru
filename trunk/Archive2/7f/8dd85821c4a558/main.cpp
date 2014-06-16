#include <iostream>
#include <type_traits>
#include <typeinfo>

using namespace std;

struct B
{
    virtual ~B() {}
    
    virtual void h() = 0;
};

struct D1 : virtual B
{
    void h() {}
};

struct D2 : virtual B
{};

struct D3 : D1, D2 {};

int main(void)
{
    D3 d;
    
    // return 0;
}
