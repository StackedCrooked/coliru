#include <iostream>
using namespace std;

void fnc(int, long, double*){}
template<int I> void f(int, long, double*){}

int main()
{
    auto a=fnc;  //(1)
    auto b=f<4>;  //(2) error
}