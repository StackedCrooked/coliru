#include <iostream>
#include <string>
#include <vector>

template <typename T>
class A
{
template <template <class X> class Z> friend class C;
private:
    void f() { std::cout << "This is A" << std::endl; }
};

template <typename T>
class B : public A<T>
{
public:
    void f() { std::cout << "This is B" << std::endl; }
};

template <template <class X> class T>
class C
{
public:
    void f() {
        T<X> b;
        b.A<X>::f();
    }
};

int main()
{
    C<int, B> c;
    c.f();
}
