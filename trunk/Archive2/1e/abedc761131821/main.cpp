#include <iostream>
#include <typeinfo>

using std::cout;
using std::endl;

struct A
{
    int b = 5;
    static const int a = 5;
};

int main()
{
    A *p = (A*)0xa31a3442;
    cout << p -> a; //Well-fromed, there is no-compile
    cout << p -> b; //Segmentation fault is producing
}