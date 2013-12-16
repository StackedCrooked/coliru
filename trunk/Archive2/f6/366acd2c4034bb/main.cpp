#include <iostream>

using namespace std;

typedef void(*FuncPtr0)();
typedef void(*FuncPtr1)(int);

void p1f()
{
    cout << "ONE";
}

void p2f(int x)
{
    cout << "TWO " << x ;
}

int main()
{
    FuncPtr0 p0;
    p0 = reinterpret_cast<FuncPtr0>(p2f);
    p0();
}