#include <iostream>
#include <functional>

using namespace std;
using namespace placeholders;

void f(int a, int b)
{
    cout << a << " " << b << endl;
}

void g(int& a, int& b)
{
    a *= 2;
    b *= 3;
}

int main()
{
    int a = 100;
    int b = 200;
    auto greversed = bind(g,_2,_1);
    greversed(b,a);
    f(a,b);
    greversed(ref(b),ref(a));
    f(a,b);
}