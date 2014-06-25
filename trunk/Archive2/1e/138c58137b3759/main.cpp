#include <iostream>
#include <string>
#include <vector>

template <typename T>
class A
{
template <class Y, template <class> class Z> friend class C;
private:
    void f() { std::cout << "This is A" << std::endl; }
};

template <typename T>
class B : public A<T>
{
public:
    void f() { std::cout << "This is B" << std::endl; }
};

template <class Y, template <class> class T>
class C
{
public:
    void f() {
        T<Y> b;
        b.A<Y>::f();
    }
};

int main()
{
    C<int, B> c;
    c.f();
}
