#include <iostream>

template<class T, class U>
void f(T t, U u)
{
    std::cout << "oi!\n";
}

template<class T>
class X
{
    template <class U>
    friend void f(T t, U u)
    {
        X x;
        x.i = 0;
        std::cout << "hey\n";
    }
    int i;
};

struct bar {};

int main()
{
    int i;
    bar b;

    f(i,b);
    f(b,i);
    X<int> x;
    f(i,b);
    f(b,i);
}
