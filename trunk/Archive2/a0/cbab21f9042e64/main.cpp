#include <iostream>
struct A
{
    A(){ }
    mutable int a;
};
const A a;

int main()
{
    a.a = 4;
    std::cout << a.a;
}