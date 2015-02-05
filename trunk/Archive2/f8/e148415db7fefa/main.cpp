#include <iostream>

using std::cout;
using std::endl;

struct A
{
    constexpr int operator[](int a)
    {
        return a;
    }
    
    constexpr operator int()
    {
        return 1;
    }
} a;

template <int a>
int foo()
{
    return a;
};

int main(){ cout << foo<a[4 >> 1]>() << endl; }