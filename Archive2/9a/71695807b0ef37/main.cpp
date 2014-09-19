#include <iostream>
using namespace std;

void fnc(int, long, double*){}
template<int I> void f(int, long, double*){}

int main()
{
    bool a=fnc;  //(1)
    bool b=f<4>;  //(2) error
}