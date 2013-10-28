#include <sstream>
#include <iostream>
#include <vector>

template<typename T>
struct A
{
    void f() { using type = typename T::type; }
};

int main()
{
    A<int> a;
    //a.f();
}