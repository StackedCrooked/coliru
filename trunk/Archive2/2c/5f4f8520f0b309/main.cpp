//test.cpp
#include <iostream>
using namespace std;

template <int SIZE, class T>
struct A
{
    void g(int x, const T& t)
    {
        t.template f<SIZE>(x);
    }
};

struct B
{
    template <int SIZE>
    void f(int x) const
    {
        cout << SIZE << ": " << x << endl;
    }
};

int main(void)
{
    A<3, B> a;
    B b;
    a.g(9, b);
    return 0;
}
