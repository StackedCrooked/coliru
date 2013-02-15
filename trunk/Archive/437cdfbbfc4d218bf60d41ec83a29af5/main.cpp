#include <limits>
#include <iostream>
#include <memory>
#include <functional>
#include <vector>
#include <algorithm>
#include <type_traits>

using std::cout;
using std::endl;

struct stuff
{
    float f;
    
    operator float const&() const { return f; }
    operator float&() { return f; }
};

template<class T>
void func(const T&) { cout<<"default"<<endl; }

template<>
void func<stuff>(const stuff&) { cout<<"spec"<<endl; }

void floatfunc(const float& f) { cout<<f<<endl; }

int main()
{    
    stuff s;
    s.f = 6.66;
    
    func(s);
    floatfunc(s);
}