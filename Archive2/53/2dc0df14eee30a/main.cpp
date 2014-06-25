#include <iostream>
#include <string>
#include <vector>

template <typename T>
class A
{
template <typename X> friend class C;
private:
    void f() { std::cout << "This is A" << std::endl; }
};

template <typename T>
class B : public A<T>
{
public:
    void f() { std::cout << "This is B" << std::endl; }
};

template <typename T>
class C
{
public:
    void f() {
        B<int> b;
        b.A::f();
    }
};

int main()
{
    C<int> c;
    c.f();
}
