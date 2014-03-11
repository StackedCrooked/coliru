#include <iostream>
typedef void (*vfunp)(...);

struct bar
{
    template<class T>
    friend bool operator<(T, bar) { return true; }
};

template <typename A>
struct X
{
    void a1 () { (vfunp)A::foo<bar()>(5); };
    void a2 () { (vfunp)A::template foo<bar()>(5); }
};
 
struct Y
{
    static void foo(...) { }
    template <class T> static vfunp foo(...) { std::cout << "Oops!" << std::endl; return nullptr; }
};
 
int main ()
{
    X<Y> moo;
    moo.a1();
    moo.a2();
}